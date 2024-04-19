# Trabajo Práctico Final 
## Protocolos de Comunicaciones en Sistemas Embebidos
### Descripción
El objetivo del proyecto es desplazar la posición de un LED a través de una matriz de LED de 8x32 moviendo un acelerómetro. Cada vez que el usuario lo mueve, se activa un registro interno del acelerómetro, lo que permite determinar que hay una nueva lectura de coordenadas disponible. A partir de estas coordenadas, el valor debe ser decodificado para establecer una correlación entre la coordenada obtenida y la posición de un LED encendido dentro de la matriz. Una vez hecho esto, el LED se enciende en la posición correspondiente, y el valor de la coordenada se muestra a través de UART. Por otro lado, el acelerómetro tiene 4 sensibilidades de medición diferentes. Para seleccionar la sensibilidad deseada, se utilizará un botón. Si se presiona el botón dos veces seguidas, la sensibilidad del acelerómetro disminuirá; mientras que si se presiona solo una vez, la sensibilidad aumentará.

### Autor
Lucas Pablo Meoli

### Docente
Israel Pavelek

### Fecha de entrega
20/04/2024