# Informe de Avance 1: Agosto 2026

## 05/08/2026 — Semana 1

En esta fecha se realizó un análisis inicial del proyecto, definiendo el problema a resolver, el objetivo general y una primera propuesta de funcionamiento.

El proyecto se planteó como un sistema automatizado de riego para el proceso de curado de ladrillos ecológicos, tomando como referencia una necesidad real existente en la fábrica. La idea consiste en desarrollar primero una maqueta funcional para UTU y utilizarla como prueba de concepto para una posible implementación futura a mayor escala.

### Tareas completadas

- Se identificó el problema principal: la necesidad de mantener una humedad adecuada durante el curado de los ladrillos.
- Se definió como objetivo automatizar parte del proceso de riego.
- Se decidió utilizar una ESP32 como controlador principal del sistema.
- Se planteó utilizar un sensor de humedad para obtener información sobre el estado de la zona de curado.
- Se propuso utilizar una bomba de agua para transportar agua desde un depósito hacia el sistema de riego.
- Se comenzó a definir la estructura general del sistema:

  ```text
  Sensor de humedad
          ↓
        ESP32
          ↓
  Sistema de control
          ↓
    Bomba de agua
          ↓
    Caños de riego
          ↓
    Zona de curado
  ```

- Se determinó que la maqueta deberá representar tres partes principales:
  - sistema electrónico de control;
  - sistema hidráulico;
  - zona de curado de los ladrillos.

### Problemas encontrados y soluciones/alternativas propuestas

Durante esta primera etapa todavía no estaban definidos todos los componentes ni la forma definitiva de construir el sistema.

Uno de los principales puntos a resolver fue determinar cómo controlar una bomba de agua desde una ESP32, ya que el microcontrolador no puede alimentar directamente una bomba.

Como solución se planteó utilizar un elemento intermedio de control, como un relé, permitiendo que la ESP32 solamente envíe la señal de activación.

También se observó que era necesario mantener separada la electrónica de la zona donde se utilizaría agua, por lo que se propuso diseñar la maqueta con una zona seca para los componentes electrónicos y una zona húmeda para el sistema de riego.

Otro aspecto todavía pendiente era determinar las dimensiones, materiales y disposición física de la maqueta.

### Próximos pasos

- Investigar los componentes necesarios.
- Revisar los componentes electrónicos disponibles.
- Seleccionar el tipo de bomba de agua.
- Conseguir o seleccionar un sensor de humedad.
- Realizar las primeras pruebas con la ESP32.
- Diseñar un primer esquema de conexiones.
- Definir la distribución física de la maqueta.
- Comenzar el diseño del sistema de riego y del depósito de agua.

### Imágenes o videos ilustrativos del avance

Para documentar esta etapa se pueden incluir:

- dibujo o esquema inicial del funcionamiento del sistema;
- fotografía de los componentes disponibles;
- boceto inicial de la maqueta;
- diagrama:

  ```text
  DEPÓSITO → BOMBA → CAÑOS DE RIEGO → ZONA DE CURADO

                         ↑
                       ESP32
                         ↑
                 SENSOR DE HUMEDAD
  ```

**Estado al finalizar la semana:** proyecto definido conceptualmente y listo para comenzar la selección de componentes y las primeras pruebas electrónicas.

## 12/08/2026 — Semana 2

Durante esta semana se continuó con la planificación del sistema y se realizó una revisión de los componentes disponibles, con el objetivo de determinar cuáles podían utilizarse en el prototipo y cuáles sería necesario conseguir.

También se definió con mayor precisión la arquitectura inicial de la maqueta y la forma en que se realizaría el circuito de agua.

### Tareas completadas

- Se realizó un inventario de los componentes electrónicos disponibles.
- Se definieron como materiales a utilizar en el proyecto:
  - ESP32 como controlador principal;
  - módulo relé de 5 V para controlar la bomba;
  - contactor para realizar la conmutación de la bomba;
  - 2 o 3 LEDs;
  - resistencias de 220 Ω;
  - un botón;
  - una bomba de agua;
  - una pantalla LCD de 16 × 2;
  - cables Dupont;
  - un sensor capacitivo de humedad;
  - una protoboard.
- Se definió que el primer prototipo trabajaría principalmente con baja tensión.
- Se incorporaron una bomba de agua, un módulo relé y un contactor para realizar las pruebas del sistema de riego.
- Se determinó que sería conveniente utilizar un sensor capacitivo de humedad, debido a que estará en contacto con un material húmedo durante largos períodos.
- Se comenzó a definir el circuito hidráulico de la maqueta:

  ```text
  Depósito de agua
          ↓
        Bomba
          ↓
  Manguera / caños de riego
          ↓
    Zona de curado
          ↓
       Drenaje
  ```

- Se planteó la posibilidad de que el agua pudiera volver al depósito, formando un pequeño sistema de recirculación.
- Se definió que la ESP32 podría generar una interfaz web local para controlar el sistema desde un celular o una computadora conectada a la misma red.
- Para esta primera versión se decidió mantener el sistema sencillo, sin depender de servidores externos ni servicios de Internet.

### Problemas encontrados y soluciones/alternativas propuestas

Uno de los problemas encontrados fue determinar la forma segura de controlar la bomba de agua, ya que no puede conectarse directamente a un pin de la ESP32 porque el microcontrolador no puede entregar la corriente necesaria.

Como solución, se planteó utilizar un módulo relé y un contactor como elementos intermedios de control. La ESP32 enviaría la señal de activación al relé, el relé accionaría la bobina del contactor y el contactor permitiría conectar o desconectar la alimentación de la bomba.

  ```text
  ESP32
    ↓
  Módulo relé
    ↓
  Contactor
    ↓
  Bomba de agua
  ```

Otro punto a resolver fue la forma de detectar la humedad. Se evaluó utilizar un sensor de humedad y se eligió como alternativa preferente un sensor capacitivo, debido a su mayor adecuación para permanecer en ambientes húmedos.

También se consideró que el contactor debe utilizarse con la tensión correspondiente a su bobina y con las protecciones adecuadas. Para la maqueta se mantendrá la parte de control en baja tensión y no se realizarán conexiones de tensión de red sin supervisión docente y las medidas de seguridad necesarias.

También se comenzó a considerar la necesidad de separar físicamente:

  ```text
  Zona electrónica
        ↕
  Zona de agua / curado
  ```

para evitar que el agua pueda alcanzar la ESP32 u otros componentes electrónicos.

### Próximos pasos

- Comenzar las primeras pruebas de conexión con la ESP32.
- Realizar pruebas con los LEDs y sus resistencias antes de conectar la bomba.
- Probar el funcionamiento del módulo relé con la ESP32.
- Verificar el accionamiento de la bobina del contactor antes de conectar la bomba.
- Comenzar las conexiones de la pantalla LCD.
- Diseñar con mayor detalle el depósito, la zona de curado y el drenaje.
- Preparar un primer esquema completo de conexiones.
- Comenzar a desarrollar el código inicial de control.

### Imágenes o videos ilustrativos del avance

Para documentar esta semana se incluirán:

- imágenes ilustrativas del proyecto;
- diagramas hechos a mano;
- fotografías reales del sistema y de las pruebas realizadas;
- fotografías y videos de la primera versión del prototipo armado;
- esquema inicial del circuito hidráulico;
- boceto de la distribución de la maqueta;

#### Fotografías reales del sistema

Fotografía de la ESP32 utilizada en las primeras pruebas:

![ESP32 utilizada en las pruebas](../proyecto%20steam/IMG_20260813_134350.jpg)

Fotografía de la pantalla LCD conectada a la protoboard:

![Pantalla LCD conectada a la protoboard](../proyecto%20steam/IMG_20260814_202030.jpg)

Fotografía del montaje de la ESP32, la pantalla LCD y los cables de conexión:

![Montaje de la ESP32 y la pantalla LCD](../proyecto%20steam/IMG_20260814_202040.jpg)

Fotografía de la bomba de agua utilizada o considerada para el sistema:

![Bomba de agua del sistema](../proyecto%20steam/image-1786809502296.jpg)

Fotografía de una prueba de conexión del sistema electrónico:

![Prueba de conexión del sistema electrónico](../proyecto%20steam/6633f6d0-f881-4dc1-ac26-54a1c4a36d7e.jpeg)

#### Imágenes ilustrativas del proyecto armado

Vista general de la maqueta del sistema de riego remoto para el curado de eco-bricks:

![Vista general de la maqueta del sistema de riego remoto](../proyecto%20steam/file_00000000caec820ebbcb0e6659aeeeb0.png)

Vista del prototipo con la zona electrónica, el depósito de agua, la bomba, la pantalla LCD, el sensor de humedad y la zona de curado:

![Prototipo armado del sistema de riego remoto](../proyecto%20steam/file_000000006d04820e8ba456fac340b887.png)

Diagrama hecho a mano del sistema, donde se representa de forma más detallada la relación entre el tablero seco, la ESP32, el relé, el contactor, la bomba, la fuente de agua y la pieza de curado:

![Diagrama más prolijo hecho a mano del sistema de riego](../proyecto%20steam/diagrama%20mas%20prolijo.jpeg)

#### Representación del sistema

  ```text
             SENSOR DE HUMEDAD
                    │
                    ▼
                  ESP32
               ┌────┴────┐
               ▼         ▼
             LCD         RELÉ
                           │
                           ▼
                        CONTACTOR
                           │
                           ▼
                    BOMBA DE AGUA
                           │
                           ▼
  DEPÓSITO ─────────► CAÑOS DE RIEGO
                           │
                           ▼
                    ZONA DE CURADO
                           │
                           ▼
                        DRENAJE
  ```

**Estado al finalizar la semana:** se definieron los materiales que se utilizarán, se detalló la arquitectura inicial del prototipo y quedaron planteadas las primeras pruebas de hardware para comenzar la implementación.

## 19/08/2026 — Semana 3

Durante esta semana se comenzó con la implementación práctica del proyecto. Se realizaron pruebas de comunicación con la ESP32, se solucionaron problemas de conexión y se confirmó que la placa puede ser programada correctamente.

Además, se modificó la idea inicial de utilizar una bomba de baja tensión y se decidió emplear una bomba de agua de 220 V, con el objetivo de que la maqueta represente de forma más fiel el funcionamiento que podría utilizarse posteriormente en una instalación real.

### Tareas completadas

- Se conectó la ESP32 a una computadora para comenzar las primeras pruebas.
- Inicialmente se intentó trabajar desde Windows, pero no se logró detectar correctamente el puerto de comunicación.
- Se realizaron las pruebas posteriormente desde Fedora Linux.
- Fedora reconoció correctamente la ESP32 mediante el puerto `/dev/ttyUSB0`.
- Se identificó el adaptador USB-Serial CP210x utilizado por la placa.
- Se configuró Arduino IDE para trabajar con la ESP32.
- Inicialmente se había seleccionado una placa ESP32-S2 incorrecta, lo cual generaba un error durante la carga.
- Se corrigió la configuración seleccionando una placa compatible con la ESP32 utilizada.
- Se logró cargar correctamente un programa de prueba en la ESP32.
- Se confirmó que la placa está operativa y preparada para continuar desarrollando el sistema.
- Se realizaron también pruebas utilizando Vento para programar la ESP32.
- Se definió que durante el desarrollo inicial se pueden utilizar LEDs para representar el estado de la bomba antes de conectar la parte de 220 V.

### Selección de la bomba

Durante esta semana se consiguió una bomba de agua para utilizar en la maqueta.

**Modelo:** RS Electrical RS-701

**Características indicadas:**

- Tensión: 220–240 V AC;
- frecuencia: 50 Hz;
- potencia: 3 W;
- caudal máximo: 230 L/h;
- altura máxima: 0,5 m;
- protección: IPX8.

Se comprobó que se trata de una bomba de agua sumergible y no de una bomba de aire. Debido a que trabaja con 220 V, se decidió incorporar un sistema de control de potencia independiente de la ESP32.

### Definición del sistema eléctrico

Se comenzó a estudiar cómo controlar de forma segura una bomba de 220 V utilizando la ESP32.

**Circuito de potencia:**

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

**Circuito de mando:**

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

También se definió que los terminales A1 y A2 corresponden a la bobina del contactor y no deben confundirse con la conexión de tierra.

### Diseño físico del controlador

Se comenzó también a trabajar en el diseño de una carcasa impresa en 3D para organizar los componentes electrónicos.

El controlador deberá contener:

- ESP32;
- pantalla LCD de 16 × 2;
- 3 LEDs;
- 3 resistencias;
- potenciómetro;
- cableado interno;
- conexión para el sensor de humedad.

Se definió que la ESP32 deberá colocarse de manera que sus dos filas de pines permanezcan accesibles, el puerto micro-USB quede orientado hacia el lateral derecho, se pueda conectar el cable USB sin desmontar la placa y la placa pueda fijarse utilizando sus agujeros de montaje.

También se encontró un modelo 3D existente para montar la pantalla LCD de 16 × 2, que puede utilizarse como referencia para desarrollar la carcasa completa.

### Problemas encontrados y soluciones/alternativas propuestas

Uno de los principales problemas fue que inicialmente la computadora no permitía comunicarse correctamente con la ESP32.

  ```text
  Windows
      ↓
  ESP32 no detectada correctamente

  Solución:

  Fedora Linux
      ↓
  /dev/ttyUSB0 detectado
      ↓
  Arduino IDE configurado
      ↓
  Carga exitosa
  ```

Otro problema fue haber seleccionado inicialmente una placa incorrecta dentro de Arduino IDE. El sistema intentaba programar la ESP32 como si fuera una ESP32-S2, provocando errores. Se solucionó seleccionando la placa ESP32 correcta.

También se detectó que la ESP32 es demasiado ancha para utilizar cómodamente una protoboard convencional, ya que una de las filas de pines queda sin espacio para conectar cables. Como alternativa, durante las pruebas se podrán utilizar cables Dupont directamente y, en el montaje definitivo, la ESP32 irá instalada directamente en la carcasa con ambas filas de pines libres y accesibles desde atrás.

Otro cambio importante fue sustituir la idea inicial de una bomba de baja tensión por una bomba de 220 V. Esto hizo necesario incorporar protección eléctrica, contactor y relé, y separar claramente la electrónica de baja tensión de la instalación de potencia.

### Próximos pasos

- Comprar un contactor adecuado para la bomba.
- Seleccionar la protección eléctrica correspondiente.
- Conseguir el cableado necesario para la parte de 220 V.
- Realizar pruebas con el módulo relé sin conectar todavía la bomba.
- Conectar y probar los 3 LEDs.
- Conectar la pantalla LCD de 16 × 2.
- Incorporar el potenciómetro para regular el contraste.
- Conseguir y probar el sensor capacitivo de humedad.
- Continuar diseñando la carcasa impresa en 3D.
- Imprimir una primera versión del soporte.
- Diseñar la caja separada para la parte eléctrica de 220 V.
- Posteriormente integrar contactor, relé y bomba.
- Construir el depósito y el sistema de caños de riego.

### Imágenes o videos ilustrativos del avance

Para esta semana conviene incluir fotografías de la ESP32 utilizada, capturas de Arduino IDE con la placa configurada, capturas o fotografías mostrando `/dev/ttyUSB0`, una carga exitosa del programa, la bomba RS-701 y su etiqueta técnica, los esquemas del circuito de potencia y de `ESP32 → relé → contactor`, además de imágenes del diseño preliminar de la carcasa 3D y del soporte para la pantalla LCD.

También se conservarán como evidencia las fotografías reales, los diagramas manuscritos y los videos de pruebas que se encuentran en la carpeta del proyecto:

#### Fotografías reales de las pruebas y componentes

![ESP32 en protoboard](../proyecto%20steam/IMG_20260813_134356.jpg)
![Pantalla LCD durante las pruebas](../proyecto%20steam/IMG_20260814_202034.jpg)
![Montaje electrónico con LCD y cables](../proyecto%20steam/IMG_20260814_202047.jpg)
![Prueba de la ESP32 y la pantalla](../proyecto%20steam/IMG_20260814_202052.jpg)
![Prueba del montaje electrónico](../proyecto%20steam/IMG_20260814_192135.jpg)
![Otra prueba del montaje electrónico](../proyecto%20steam/IMG_20260814_192142.jpg)
![Montaje electrónico en la protoboard](../proyecto%20steam/IMG_20260814_235833.jpg)
![Pantalla LCD encendida](../proyecto%20steam/IMG_20260815_001214.jpg)
![Pantalla LCD durante la prueba](../proyecto%20steam/IMG_20260815_001349.jpg)
![Mensaje de prueba en la pantalla LCD](../proyecto%20steam/IMG_20260815_001426.jpg)
![Prueba general de la conexión](../proyecto%20steam/IMG_20260815_001809.jpg)
![ESP32 utilizada en otra prueba](../proyecto%20steam/image-1786644512444.jpg)
![Otra vista de la ESP32](../proyecto%20steam/image-1786644683922.jpg)
![Bomba de agua](../proyecto%20steam/image-1786809518041.jpg)

#### Diagramas manuscritos

![Diagrama manuscrito del sistema](../proyecto%20steam/image-1786491987050.jpg)
![Diagrama manuscrito de conexiones](../proyecto%20steam/image-1786493063435.jpg)
![Diagrama manuscrito de la maqueta](../proyecto%20steam/image-1786493418331.jpg)
![Diagrama manuscrito del circuito](../proyecto%20steam/image-1786493877779.jpg)
![Diagrama manuscrito alternativo](../proyecto%20steam/image-1786495545867.jpg)
![Diagrama manuscrito del sistema hidráulico](../proyecto%20steam/image-1786495912956.jpg)

- [Video de prueba del sistema 1](../proyecto%20steam/VID_20260814_235908.mp4)
- [Video de prueba del sistema 2](../proyecto%20steam/VID_20260815_001320.mp4)
- [Página técnica y estructura inicial del código](../proyecto%20steam/conexiones%20esp32.html)

Puede incluirse además este esquema general:

  ```text
                         CONTROL
  Sensor de humedad
          │
          ▼
        ESP32
       ┌──┴─────────────┐
       ▼                ▼
  LCD / LEDs           Relé
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

**Estado al finalizar la semana:** la ESP32 quedó correctamente configurada y programable, se adquirió la bomba definitiva para la maqueta, se definió la arquitectura de control de una carga de 220 V y se comenzó el diseño físico del módulo electrónico. El proyecto pasó de la etapa de planificación a una primera etapa de implementación real.

## [x]/8/2026
- [Realizar una descripción de los avances en el proyecto en la fecha en uno o dos párrafos]
- [Incluir:]
  - [Tareas completadas]
  - [Problemas encontrados y soluciones/alternativas propuestas]
  - [Próximos pasos]
  - [Imágenes o videos ilustrativos del avance]

## Nota
En este enlace encontrarás un [ejemplo como debe completarse el informe de avance](avance_ejemplo.md).
