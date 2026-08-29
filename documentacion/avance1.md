# Informe de Avance 1: Agosto 2026

## 08/08/2026 - Semana 1: definición de la idea del proyecto

Durante esta semana se definió la idea principal del proyecto STEAM: construir una maqueta funcional de un sistema de riego remoto para el curado de ladrillos ecológicos.

El proyecto se basa en una necesidad real de una fábrica familiar. En este tipo de ladrillo, el curado no se realiza mediante horno, sino mediante humectación. Por eso se propone representar un sistema que permita activar el riego de forma remota, segura y controlada.

### Tareas completadas

- Se eligió el tema del proyecto.
- Se definió que la versión para UTU será una maqueta funcional en baja tensión.
- Se separó la versión educativa de una posible implementación futura en el entorno real.
- Se decidió usar un ESP32 como controlador principal.
- Se decidió usar una mini bomba de agua en lugar de una bomba de 220 V.

### Problemas encontrados y soluciones propuestas

El sistema real utilizaría una bomba de mayor potencia, pero no es seguro ni necesario trabajar con 220 V en la maqueta. Por ese motivo, se resolvió construir la primera versión únicamente con componentes de baja tensión.

### Próximos pasos

- Revisar los componentes electrónicos disponibles.
- Definir la arquitectura inicial del sistema.
- Identificar los materiales que será necesario conseguir.
- Diseñar la distribución física de la maqueta.

## 12/08/2026 - Semana 2: planificación y revisión de componentes

Durante esta semana se continuó con la planificación del sistema y se realizó una revisión de los componentes disponibles, con el objetivo de determinar cuáles podían utilizarse en el prototipo y cuáles sería necesario conseguir.

También se definió con mayor precisión la arquitectura inicial de la maqueta y la forma en que se realizaría el circuito de agua.

### Tareas completadas

- Se realizó un inventario de los componentes electrónicos disponibles.
- Se identificaron o seleccionaron como útiles para el proyecto:
  - ESP32 como controlador principal.
  - Módulo relé de 5 V.
  - Protoboard.
  - Cables Dupont.
  - LEDs.
  - Resistencias de 220 Ω.
  - Pulsadores.
  - Potenciómetros.
  - Sensor ultrasónico HC-SR04 como posible sensor para medir el nivel del depósito.
  - Pantalla LCD para mostrar información del sistema.
- Se definió que el primer prototipo trabajaría principalmente con baja tensión y utilizaría una bomba pequeña controlada mediante un relé.
- Se seleccionó como opción una mini bomba de agua de 3 a 6 V para realizar las primeras pruebas.
- Se determinó que sería conveniente utilizar un sensor capacitivo de humedad, debido a que estará en contacto con material húmedo durante períodos prolongados.
- Se definió que el ESP32 podrá generar una interfaz web local para controlar el sistema desde un celular o una computadora conectada a su red.
- Se decidió mantener la primera versión sencilla, sin depender de servidores externos ni servicios de Internet.

### Circuito hidráulico preliminar

```text
Depósito de agua
       ↓
     Bomba
       ↓
Manguera o caños de riego
       ↓
 Zona de curado
       ↓
    Drenaje
```

También se planteó la posibilidad de que el agua vuelva al depósito para formar un pequeño sistema de recirculación.

### Arquitectura inicial del sistema

```text
          Sensor de humedad
                 │
                 ▼
               ESP32
            ┌────┴────┐
            ▼         ▼
           LCD       Relé
                       │
                       ▼
                     Bomba
                       │
                       ▼
Depósito ─────────► caños de riego
                       │
                       ▼
                Zona de curado
                       │
                       ▼
                    Drenaje
```

![Prototipo conceptual](imagenes/prototipo_riego_curado_utu.webp)

### Problemas encontrados y soluciones propuestas

El kit de componentes disponible no incluye una bomba de agua ni un sensor capacitivo de humedad, por lo que será necesario conseguirlos por separado.

También se determinó que la bomba no puede conectarse directamente a un pin del ESP32, porque el microcontrolador no entrega la corriente necesaria. Como solución, se propuso utilizar el siguiente esquema:

```text
ESP32
  ↓
Relé
  ↓
Bomba con alimentación adecuada
```

De esta forma, el ESP32 solamente enviará la señal de control y el relé conectará o desconectará la alimentación de la bomba.

Para detectar la humedad se evaluaron distintas alternativas y se eligió como opción preferente un sensor capacitivo, por ser más adecuado para permanecer en ambientes húmedos.

También se comenzó a considerar la separación física entre la zona electrónica y la zona de agua y curado, para evitar que el agua alcance el ESP32, el relé u otros componentes.

### Próximos pasos

- Conseguir la mini bomba de agua.
- Conseguir el sensor capacitivo de humedad.
- Comenzar las primeras pruebas de conexión con el ESP32.
- Probar el funcionamiento del módulo relé.
- Realizar pruebas con LEDs antes de conectar la bomba.
- Comenzar las conexiones de la pantalla LCD.
- Diseñar con mayor detalle el depósito, la zona de curado y el drenaje.
- Preparar un primer esquema completo de conexiones.
- Comenzar a desarrollar el código inicial de control.

### Material visual pendiente

Cuando se encuentre disponible, se podrá incorporar:

- Una fotografía de los componentes electrónicos.
- Una fotografía del ESP32, el relé y la protoboard.
- Un esquema del circuito hidráulico.
- Un boceto de la distribución física de la maqueta.

### Estado al finalizar la semana

Se identificaron los componentes disponibles y faltantes, se definió con mayor detalle la arquitectura inicial del prototipo y quedaron planteadas las primeras pruebas de hardware necesarias para comenzar la implementación.

## 19/08/2026 - Semana 3: primeras pruebas con ESP32 y definición de la bomba

Durante esta semana se comenzó con la implementación práctica del proyecto. Se realizaron pruebas de comunicación con la ESP32, se solucionaron problemas de conexión y se confirmó que la placa puede ser programada correctamente.

Además, se modificó la idea inicial de utilizar una bomba de baja tensión y se decidió emplear una bomba de agua de 220 V. Este cambio permite que la maqueta represente de forma más fiel el funcionamiento que podría utilizarse posteriormente en una instalación real, aunque también requiere separar claramente la electrónica de control de la parte de potencia.

### Tareas completadas

- Se conectó la ESP32 a una computadora para comenzar las primeras pruebas.
- Inicialmente se intentó trabajar desde Windows, pero no se logró detectar correctamente el puerto de comunicación.
- Se realizaron las pruebas posteriormente desde Fedora Linux.
- Fedora reconoció correctamente la ESP32 mediante el puerto `/dev/ttyUSB0`.
- Se identificó el adaptador USB-Serial CP210x utilizado por la placa.
- Se configuró Arduino IDE para trabajar con la ESP32.
- Al principio se había seleccionado una placa ESP32-S2 incorrecta, lo cual generaba errores durante la carga.
- Se corrigió la configuración seleccionando una placa compatible con la ESP32 utilizada.
- Se logró cargar correctamente un programa de prueba en la ESP32.
- Se confirmó que la placa está operativa y preparada para continuar desarrollando el sistema.
- Se realizaron también pruebas utilizando Vento para programar la ESP32.
- Se definió que durante el desarrollo inicial se pueden utilizar LEDs para representar el estado de la bomba antes de conectar la parte de 220 V.

### Bomba seleccionada

Durante esta semana se consiguió una bomba de agua para utilizar en la maqueta.

Modelo: RS Electrical RS-701

Características:

```text
Tensión:        220-240 V AC
Frecuencia:     50 Hz
Potencia:       3 W
Caudal máximo:  230 L/h
Altura máxima:  0,5 m
Protección:     IPX8
```

Se comprobó que se trata de una bomba de agua sumergible y no de una bomba de aire. Debido a que trabaja con 220 V, se decidió incorporar un sistema de control de potencia independiente de la ESP32.

### Circuito de potencia

Se comenzó a estudiar cómo controlar de forma segura una bomba de 220 V utilizando la ESP32. Para la parte de potencia se definió la siguiente arquitectura:

```text
220 V
  │
  ▼
Protección eléctrica
  │
  ▼
Contactor
  │
  ▼
Bomba 220 V
```

### Circuito de mando

Para el circuito de mando se definió el siguiente esquema:

```text
ESP32
  │
  ▼
Relé 5 V
  │
  ▼
Bobina del contactor
  │
  ▼
Contactor
```

Se comprendió que el relé no alimentará directamente la bomba, sino que será utilizado para activar la bobina del contactor. El contactor será el encargado de conectar y desconectar la alimentación de 220 V de la bomba.

También se definió que los terminales A1 y A2 corresponden a la bobina del contactor y que no deben confundirse con la conexión de tierra.

### Diseño físico del controlador

Se comenzó a trabajar en el diseño de una carcasa impresa en 3D para organizar los componentes electrónicos.

El controlador deberá contener:

- ESP32.
- Pantalla LCD 16x2.
- 3 LEDs.
- 3 resistencias.
- Potenciómetro.
- Cableado interno.
- Conexión para sensor de humedad.

Se definió que la ESP32 deberá colocarse de manera que:

- Sus dos filas de pines permanezcan accesibles.
- El puerto micro-USB quede orientado hacia el lateral derecho.
- Se pueda conectar el cable USB sin desmontar la placa.
- La ESP32 pueda fijarse utilizando sus agujeros de montaje.

También se encontró un modelo 3D existente para montar la pantalla LCD 16x2, que puede utilizarse como referencia para desarrollar la carcasa completa.

### Problemas encontrados y soluciones propuestas

Uno de los principales problemas fue que inicialmente la computadora no permitía comunicarse correctamente con la ESP32.

Problema:

```text
Windows
   ↓
ESP32 no detectada correctamente
```

Solución:

```text
Fedora Linux
     ↓
/dev/ttyUSB0 detectado
     ↓
Arduino IDE configurado
     ↓
Carga exitosa
```

Otro problema fue haber seleccionado inicialmente una placa incorrecta dentro de Arduino IDE. El sistema intentaba programar la ESP32 como si fuera una ESP32-S2, provocando errores. Se solucionó seleccionando la placa ESP32 correcta.

También se detectó que la ESP32 es demasiado ancha para utilizar cómodamente una protoboard convencional, ya que una de las filas de pines queda sin espacio para conectar cables.

Como alternativa se decidió que:

- Durante las pruebas se podrán utilizar cables Dupont directamente.
- En el montaje definitivo la ESP32 irá instalada directamente en la carcasa.
- Ambas filas de pines quedarán libres y accesibles desde atrás.

Otro cambio importante fue sustituir la idea inicial de una bomba de baja tensión por una bomba de 220 V. Esto hizo necesario incorporar:

```text
Protección eléctrica
+
Contactor
+
Relé
```

y separar claramente la electrónica de baja tensión de la instalación de potencia.

### Esquema general actualizado

```text
                   CONTROL

Sensor humedad
      │
      ▼
    ESP32
   ┌──┴─────────────┐
   ▼                ▼
 LCD / LEDs        Relé
                     │
                     ▼
               Bobina contactor


                   POTENCIA

220 V
  │
  ▼
Protección
  │
  ▼
Contactor
  │
  ▼
Bomba RS-701
  │
  ▼
Sistema de riego
```

### Próximos pasos

- Comprar un contactor adecuado para la bomba.
- Seleccionar la protección eléctrica correspondiente.
- Conseguir el cableado necesario para la parte de 220 V.
- Realizar pruebas con el módulo relé sin conectar todavía la bomba.
- Conectar y probar los 3 LEDs.
- Conectar la pantalla LCD 16x2.
- Incorporar el potenciómetro para regular el contraste.
- Conseguir o probar el sensor capacitivo de humedad.
- Continuar diseñando la carcasa impresa en 3D.
- Imprimir una primera versión del soporte.
- Diseñar la caja separada para la parte eléctrica de 220 V.
- Posteriormente integrar contactor, relé y bomba.
- Construir el depósito y el sistema de caños de riego.

### Material visual pendiente

Para esta semana conviene incluir:

- Una fotografía de la ESP32 utilizada.
- Una captura de Arduino IDE con la placa configurada.
- Una captura o fotografía mostrando `/dev/ttyUSB0`.
- Una captura de una carga exitosa del programa.
- Una fotografía de la bomba RS-701.
- Una fotografía de la etiqueta técnica de la bomba.
- Un esquema del circuito de potencia.
- Un esquema de ESP32, relé y contactor.
- Imágenes del diseño preliminar de la carcasa 3D.
- Una imagen del soporte encontrado para el LCD 16x2.

### Estado al finalizar la semana

La ESP32 quedó correctamente configurada y programable, se adquirió la bomba definitiva para la maqueta, se definió la arquitectura de control de una carga de 220 V y se comenzó el diseño físico del módulo electrónico. El proyecto pasó de la etapa de planificación a una primera etapa de implementación real.

## 26/08/2026 - Semana 4: integración del sistema electrónico de control

Durante esta semana se avanzó en la integración completa del sistema electrónico de control del proyecto de riego para curado de ladrillos. Se conectaron y probaron la ESP32, el sensor de humedad, la pantalla LCD, el módulo relé, los LEDs indicadores, los botones físicos y un zumbador utilizado temporalmente para representar el funcionamiento de la futura bomba.

Además, se desarrolló una página web local alojada directamente en la ESP32, desde la cual es posible visualizar la humedad y controlar manualmente el riego mediante diferentes temporizadores.

### Configuración de la ESP32

Se continuó trabajando con una placa ESP32 DEVKIT V1 / ESP-WROOM-32 de 30 pines.

La configuración utilizada en Arduino IDE fue:

```text
Placa: ESP32 Dev Module
Puerto: puerto USB detectado por la computadora
Monitor serie: 115200 baudios
```

Inicialmente se cargó un programa mínimo para verificar la comunicación mediante el Monitor Serie y confirmar que la placa funcionaba correctamente.

### Sensor de humedad

Se conectó y probó un sensor capacitivo de humedad.

Conexión utilizada:

```text
Sensor VCC  → 3V3 ESP32
Sensor GND  → GND ESP32
Sensor AOUT → GPIO 34
```

Se alimentó el sensor con 3,3 V para trabajar de forma compatible con la entrada analógica de la ESP32.

También se realizó una primera calibración experimental. Los valores obtenidos fueron:

```text
Seco / aire:        aproximadamente 2463-2478
Húmedo / planta:    aproximadamente 959
```

Como valores iniciales de referencia se utilizaron:

```text
Valor seco   = 2463
Valor húmedo = 959
```

Estos valores permiten convertir posteriormente la lectura analógica en un porcentaje aproximado de humedad.

### Red WiFi e interfaz web

Se programó la ESP32 para crear su propia red WiFi local.

Configuración:

```text
Red WiFi:     CuradoLadrillos
Contraseña:   12345678

Dirección:
http://192.168.4.1
```

Esto permite conectarse directamente desde un celular o computadora sin necesidad de utilizar Internet.

Desde la interfaz web actualmente es posible:

- Visualizar el porcentaje de humedad.
- Visualizar el estado de la bomba.
- Iniciar riego durante 5 segundos.
- Iniciar riego durante 10 segundos.
- Iniciar riego durante 20 segundos.
- Detener manualmente el riego.

También se agregó una actualización automática cada 1 segundo, permitiendo que la página refleje el estado real del sistema una vez finalizado un temporizador.

La lógica general quedó:

```text
Celular / PC
     │
     ▼
WiFi CuradoLadrillos
     │
     ▼
192.168.4.1
     │
     ▼
ESP32
     │
     ▼
Control del riego
```

### Pantalla LCD 16x2

Se soldó la tira macho de 16 pines a la pantalla LCD. Primero se realizaron pruebas de alimentación y posteriormente se configuró la pantalla en modo de 4 bits.

Conexiones utilizadas:

```text
LCD 1  VSS → GND
LCD 2  VDD → VN / 5V
LCD 3  VO  → pata central del potenciómetro

LCD 4  RS  → GPIO 19
LCD 5  RW  → GND
LCD 6  E   → GPIO 23

LCD 7  D0  → sin conectar
LCD 8  D1  → sin conectar
LCD 9  D2  → sin conectar
LCD 10 D3  → sin conectar

LCD 11 D4  → GPIO 18
LCD 12 D5  → GPIO 21
LCD 13 D6  → GPIO 22
LCD 14 D7  → GPIO 13

LCD 15 A   → VN / 5V
LCD 16 K   → GND
```

El potenciómetro de 10 kΩ quedó conectado de la siguiente manera:

```text
Pata lateral 1 → VN / 5V
Pata central   → LCD pin 3 VO
Pata lateral 2 → GND
```

Durante las pruebas se observó que alimentando la pantalla desde 3,3 V las letras presentaban poco contraste. La alternativa utilizada fue alimentarla desde VN / 5V, obteniendo una visualización correcta.

### Relé, LEDs y zumbador temporal

Se integró un módulo relé de 1 canal y 5 V.

Conexión:

```text
Relé S → GPIO 26
Relé + → VN / 5V
Relé - → GND
```

Actualmente el relé no controla todavía la bomba real. Su objetivo durante esta etapa es verificar correctamente la lógica que posteriormente controlará el contactor.

En el programa quedó definido:

```text
RELAY_ACTIVE_LOW = true
```

En caso de utilizar un relé cuyo comportamiento sea inverso, este valor puede modificarse a `false`.

Se instalaron dos LEDs para representar visualmente el estado del sistema.

```text
GPIO 32
   │
resistencia 330 Ω
   │
LED rojo
   │
GND
```

El LED rojo indica que el sistema de riego se encuentra apagado.

```text
GPIO 33
   │
resistencia 330 Ω
   │
LED verde
   │
GND
```

El LED verde indica que el riego se encuentra activo.

El comportamiento implementado es:

```text
RIEGO APAGADO

LED rojo  → ENCENDIDO
LED verde → APAGADO
Relé      → APAGADO
```

```text
RIEGO ACTIVO

LED rojo  → APAGADO
LED verde → ENCENDIDO
Relé      → ACTIVADO
```

Para representar temporalmente el funcionamiento de la futura bomba se agregó un zumbador o timbre. Se conectó al lado de contactos del relé:

```text
VN / 5V
   │
   ▼
COM del relé
   │
   ▼
NO
   │
   ▼
positivo del zumbador

negativo del zumbador → GND
```

Se utilizó el contacto NO, normalmente abierto. Esto permite que el zumbador permanezca apagado cuando el relé está apagado y se encienda cuando el relé se activa.

Este componente es temporal y será retirado cuando se conecte la bomba mediante el contactor.

### Botones físicos

Se agregaron dos botones para permitir controlar el sistema directamente sin utilizar la interfaz web.

```text
GPIO 25 → botón → GND
```

Su función es iniciar un ciclo de riego de 5 segundos.

```text
GPIO 27 → botón → GND
```

Su función es detener inmediatamente el riego.

No fue necesario instalar resistencias externas debido a que el programa utiliza `INPUT_PULLUP`. De esta manera la ESP32 utiliza internamente una resistencia pull-up.

### Programa integrado

Durante esta semana se consiguió integrar en un único programa:

- WiFi local.
- Servidor web.
- Lectura del sensor de humedad.
- Conversión aproximada a porcentaje.
- Pantalla LCD 16x2.
- Módulo relé.
- LED rojo.
- LED verde.
- Zumbador temporal.
- Botón de encendido.
- Botón de apagado.
- Temporizadores.
- Apagado automático.
- Control mediante `millis()`.

El uso de `millis()` permite controlar los tiempos sin detener completamente la ejecución del programa.

Por ejemplo:

```text
Usuario solicita 10 segundos
        │
        ▼
ESP32 activa riego
        │
        ├── continúa leyendo sensores
        ├── continúa atendiendo la web
        └── controla el tiempo
                 │
                 ▼
         pasan 10 segundos
                 │
                 ▼
          riego apagado
```

### Distribución actual de pines

```text
LCD
RS → GPIO 19
E  → GPIO 23
D4 → GPIO 18
D5 → GPIO 21
D6 → GPIO 22
D7 → GPIO 13

SENSOR DE HUMEDAD
AOUT → GPIO 34

RELÉ
S → GPIO 26

BOTÓN ENCENDER
GPIO 25

BOTÓN APAGAR
GPIO 27

LED ROJO
GPIO 32

LED VERDE
GPIO 33
```

### Documentación complementaria

Además del montaje físico, se creó una página de documentación del proyecto utilizando Vento:

[Página de conexiones del prototipo ESP32](conexiones-esp32.html)

La versión original fue creada en Vento en la ruta:

```text
/networks/facu/proyectos/riego-ladrillos/conexiones-esp32.html
```

La documentación incluye conexiones completas, distribución de GPIO, conexión del LCD, conexión del sensor de humedad, conexión del módulo relé, conexión de LEDs, conexión del zumbador, conexión de botones, código utilizado y notas relacionadas con la futura bomba y el contactor.

### Problemas encontrados y soluciones propuestas

Problema: al alimentar la pantalla LCD desde 3,3 V, los caracteres se visualizaban con poco contraste.

Solución aplicada: se utilizó la alimentación VN / 5V, manteniendo el potenciómetro de 10 kΩ para regular el contraste.

Problema: todavía no se encontraba instalada la bomba de 220 V con su correspondiente contactor.

Alternativa temporal: se incorporó un zumbador conectado al relé. De esta forma, cuando el relé se activa, el zumbador suena y permite comprobar físicamente cuándo el sistema considera que la bomba debería estar funcionando.

También se consideró necesario disponer de una forma de operar el sistema incluso sin utilizar un teléfono o computadora. Como solución, se agregaron dos botones físicos: uno para iniciar el riego durante 5 segundos y otro para realizar el apagado inmediato.

Inicialmente era necesario asegurarse de que la interfaz mostrara correctamente el estado después de finalizar un temporizador. Para resolverlo, se agregó una actualización automática de la información cada 1 segundo.

### Arquitectura prevista para la bomba real

Se determinó que la bomba real no debe conectarse directamente al relé ni a la ESP32. La arquitectura prevista es:

```text
              CONTROL

ESP32
  │
  ▼
Relé
  │
  ▼
Bobina del contactor


              POTENCIA

220 V
  │
  ▼
Protección
  │
  ▼
Contactor
  │
  ▼
Bomba
```

La instalación correspondiente a 220 V será realizada o supervisada por una persona con conocimientos eléctricos.

También se planteó mantener el enchufe original de la bomba y utilizar una toma hembra controlada mediante el contactor, evitando modificar innecesariamente el cable original.

### Esquema general actualizado

```text
            SENSOR HUMEDAD
                  │
                  ▼
                ESP32
        ┌─────────┼───────────┐
        │         │           │
        ▼         ▼           ▼
       LCD      LEDs       WEB LOCAL
                              │
Botones ───────► ESP32 ◄──────┘
                  │
                  ▼
                RELÉ
                  │
           [actualmente]
                  ▼
              ZUMBADOR

           [etapa futura]

                RELÉ
                  │
                  ▼
             CONTACTOR
                  │
                  ▼
             BOMBA 220V
                  │
                  ▼
          SISTEMA DE RIEGO
```

### Próximos pasos

- Conseguir el contactor.
- Definir e instalar la protección eléctrica correspondiente.
- Realizar la conexión de potencia bajo supervisión.
- Retirar el zumbador cuando se incorpore la bomba.
- Conectar la bomba real.
- Realizar pruebas de encendido y apagado mediante contactor.
- Incorporar depósito de agua.
- Conectar mangueras.
- Construir el sistema de distribución de agua.
- Realizar la primera prueba hidráulica.
- Construir la representación de la zona de curado.
- Probar el sensor de humedad dentro del material de la maqueta.
- Continuar desarrollando la carcasa impresa en 3D para organizar los componentes.

### Material visual pendiente

Para la documentación de esta semana conviene agregar:

- Fotografía del montaje completo sobre la protoboard.
- Fotografía del sensor capacitivo introducido en material húmedo.
- Captura del Monitor Serie mostrando las lecturas del sensor.
- Fotografía de la pantalla LCD mostrando la humedad o el estado.
- Fotografía del relé conectado.
- Video corto activando el riego desde el botón físico.
- Video activando 5, 10 y 20 segundos desde la página web.
- Captura desde el celular conectado a `CuradoLadrillos` y `http://192.168.4.1`.
- Fotografía de los LEDs mostrando ambos estados.
- Video donde se escuche el zumbador al activarse el relé.
- Captura de la página de documentación creada en Vento: [conexiones-esp32.html](conexiones-esp32.html).

### Estado al finalizar la semana

El sistema electrónico de control se encuentra prácticamente funcional. Actualmente funcionan en conjunto la ESP32, la red WiFi local `CuradoLadrillos`, la página web en `192.168.4.1`, la lectura de humedad, la conversión a porcentaje, la pantalla LCD 16x2, el relé, el LED rojo, el LED verde, el zumbador temporal, los botones de encendido y apagado, el riego temporizado y el apagado automático.

La siguiente etapa importante será pasar de la simulación de la carga a controlar la bomba real mediante contactor, para después comenzar las pruebas hidráulicas sobre la maqueta.

## Registro visual de semanas 2 a 4

Las imágenes y videos correspondientes a estas semanas se encuentran en la carpeta `documentacion/imagenes/sem 2 a 4`.

### Semana 2 - componentes y primeras conexiones

- [Montaje inicial en protoboard](<imagenes/sem 2 a 4/6633f6d0-f881-4dc1-ac26-54a1c4a36d7e.webp>)
- [Primera vista del montaje](<imagenes/sem 2 a 4/IMG_20260814_184953_005.webp>)
- [LCD encendida en el montaje](<imagenes/sem 2 a 4/IMG_20260814_192135.webp>)
- [Prueba de pantalla LCD](<imagenes/sem 2 a 4/IMG_20260814_192142.webp>)
- [Conexiones de la pantalla LCD](<imagenes/sem 2 a 4/IMG_20260814_202030.webp>)
- [Detalle de conexiones del LCD](<imagenes/sem 2 a 4/IMG_20260814_202034.webp>)
- [Montaje con ESP32 y LCD](<imagenes/sem 2 a 4/IMG_20260814_202047.webp>)
- [Detalle de la ESP32 en protoboard](<imagenes/sem 2 a 4/IMG_20260814_202052.webp>)
- [Video de prueba inicial](<imagenes/sem 2 a 4/VID_20260814_235908.mp4>)

### Semana 3 - pruebas de comunicación y pantalla

- [Montaje nocturno de prueba](<imagenes/sem 2 a 4/IMG_20260814_235833.webp>)
- [LCD durante prueba de texto](<imagenes/sem 2 a 4/IMG_20260815_001214.webp>)
- [LCD encendida durante la carga](<imagenes/sem 2 a 4/IMG_20260815_001349.webp>)
- [Mensaje de prueba en la LCD](<imagenes/sem 2 a 4/IMG_20260815_001426.webp>)
- [Montaje de prueba funcionando](<imagenes/sem 2 a 4/IMG_20260815_001809.webp>)
- [Video de prueba de la ESP32 y LCD](<imagenes/sem 2 a 4/VID_20260815_001320.mp4>)

### Semana 4 - sistema electrónico integrado e interfaz web

- [Mensaje inicial en LCD con ESP32](<imagenes/sem 2 a 4/IMG_20260823_183251.webp>)
- [Lectura de humedad en pantalla LCD](<imagenes/sem 2 a 4/IMG_20260823_184211.webp>)
- [Celular conectado a la red del sistema](<imagenes/sem 2 a 4/Screenshot_20260823_183729_com_android_settings_Settings$WifiSettingsActivity.webp>)
- [Interfaz web local desde el celular](<imagenes/sem 2 a 4/Screenshot_20260823_183724_com_android_chrome_ChromeTabbedActivity.webp>)
- [Control web del sistema de riego](<imagenes/sem 2 a 4/Screenshot_20260823_183732_com_android_chrome_ChromeTabbedActivity.webp>)
- [Página web del proyecto Curado de ladrillos](<imagenes/sem 2 a 4/Screenshot_20260823_184200_com_android_chrome_ChromeTabbedActivity.webp>)
- [Video de funcionamiento del sistema](<imagenes/sem 2 a 4/VID_20260823_193420.mp4>)
- [Montaje completo con relé, LEDs y LCD](<imagenes/sem 2 a 4/IMG_20260826_194032.webp>)
- [Sistema electrónico completo sobre protoboard](<imagenes/sem 2 a 4/IMG_20260826_194048.webp>)
- [Pantalla LCD mostrando humedad](<imagenes/sem 2 a 4/IMG_20260826_201409.webp>)
- [Prueba con LED indicador](<imagenes/sem 2 a 4/IMG_20260826_201733.webp>)
- [Montaje completo con indicadores](<imagenes/sem 2 a 4/IMG_20260826_201736.webp>)
- [Vista general del montaje final de la semana](<imagenes/sem 2 a 4/IMG_20260826_201740.webp>)
