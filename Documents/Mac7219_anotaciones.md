Hay que trabajar SIN codificar para maejar los 64 leds
Tiro que si estamos con decodificador podemos trabajar con mas display, habria que chequear eso

Para configurar seria asi:}

sendData(address, data)
sendData(0x09, 0x00) -> Sin decodificar para poder usar 8x8
sendData(0x0A, 0x01) -> La intensidad en low
sendData(0x0B, 0x07) -> Aca digo que va a ser 8x8,. Aca cuando llama a digits es las columnas
sendData(0x0C, 0x01) -> Es el shutdown, es para tenerlo prendido, lo pongo enNormal Operation
sendData(0x0F, 0x00) -> Es para el test, en 0 es normal, en 1 es el display test

El address es la columna y la data cual se prende
