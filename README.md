# Sistema de riego remoto para curado de ladrillos ecológicos

## Descripción

Este proyecto STEAM busca construir una maqueta funcional de un sistema de riego remoto para el curado de ladrillos ecológicos.

El proyecto parte de una necesidad real de una fábrica familiar. A diferencia de los ladrillos tradicionales, estos ladrillos no se curan mediante horno o quemado, sino mediante humectación. Para representar y validar una posible solución en un entorno educativo, se desarrollará una maqueta funcional controlada por ESP32, con una página web local para activar el riego y visualizar información del sistema.

Durante la planificación inicial se evaluó utilizar una mini bomba de baja tensión. Luego el proyecto evolucionó hacia el uso de una bomba sumergible de 220 V, controlada mediante una etapa de mando y potencia separadas. En las primeras pruebas, el relé activa un zumbador temporal para simular la bomba antes de conectar la instalación real con contactor.

El funcionamiento previsto es el siguiente:

```text
Celular o computadora
→ red WiFi del ESP32
→ página web local
→ relé
→ contactor
→ bomba sumergible
→ manguera
→ bandeja de curado
→ drenaje
```

![Prototipo conceptual](documentacion/imagenes/prototipo_riego_curado_utu.png)

> Este proyecto se realiza durante el curso **Laboratorio STEAM+** de la tecnicatura **Redes y Software** de **UTU**. La electrónica de control trabaja con baja tensión. La parte de 220 V debe realizarse o supervisarse por una persona con conocimientos eléctricos.

## Integrante

- Facundo Pérez

## Objetivo general

Diseñar y construir una maqueta funcional que simule el riego controlado durante el curado de ladrillos ecológicos mediante un ESP32, una bomba de agua, una etapa de control con relé y contactor, y una interfaz web local.

## Objetivos específicos

- Construir una maqueta segura y demostrable, separando la electrónica de control de la etapa de potencia.
- Crear una página web local alojada en el ESP32.
- Controlar la activación del riego mediante relé y contactor.
- Permitir riegos temporizados desde un celular o una computadora.
- Mostrar el estado del sistema en una pantalla LCD 16x2.
- Medir la humedad mediante un sensor capacitivo.
- Documentar el proceso de diseño, armado, pruebas y mejoras.

## Documentación

- [Informe de Avance 1 - Agosto 2026](documentacion/avance1.md)
- [Informe de Avance 2 - Septiembre 2026](documentacion/avance2.md)
- [Informe de Avance 3 - Octubre 2026](documentacion/avance3.md)
- [Documentación técnica](documentacion/documentacion_tecnica.md)
- [Página de conexiones del prototipo ESP32](documentacion/conexiones-esp32.html)

## Estado actual

El sistema electrónico de control ya integra ESP32, red WiFi local, página web, sensor capacitivo de humedad, LCD 16x2, relé, LEDs indicadores, botones físicos y un zumbador temporal para simular la bomba. La siguiente etapa es conectar la bomba real mediante contactor y comenzar las pruebas hidráulicas de la maqueta.
