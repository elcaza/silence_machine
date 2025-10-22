# Silence Machine - Single Core
La máquina generadora de silencio. Versión de un solo núcleo. 

La máquina generadora de silencio es un dispositivo que te ayuda a recobrar la paz perdida cuando la bocina ruidosa de tu vecino suena a máximo volumen. 

Para entender su funcionamiento necesitamos entender lo siguiente:
1. La música es la combinación de sonidos, ritmos y silencios.
1. Pese a las reglamentaciones locales, las autoridades informan que no pueden hacer nada en contra de las bocinas ruidosas que suenan dentro de los domicilios. "Que pongas tu música también", dicen.
1. Dado lo anterior, solo quedaba una cosa por hacer. Poner mi música a todo volumen, siendo mi música una combinación de silencios a un volumen muy fuerte.

Señoras y señores, me complace presentarles a la máquina generadora de silencio.

## Componentes requeridos
+ ESP32 o similar. 30 o 38 pines, son bienvenidos.
+ 2 módulos de radio a 2.4 Ghz
+ Pantala OLED con botones
+ 2 Capacitores

# Modo de operación
1. Prende el dispositivo
1. Se corre de forma automática un chequeo de salud, se muestra el resultado en pantalla
	+ Si todo sale bien, puedes proseguir 
	+ Si alguno de los módulos RF falla, el resultado se mostrara en pantalla
	+ Si la pantalla falla, en el Serial se mostrará el error
	+ Muchas veces solo con reiniciarlo, `botón #`, se corregirá el error
1. Seleccionas
	+ `#` => para reiniciar
	+ `*` => para continuar
1. Seleccionas un modo y generas silencio
	+ `^` => arriba
	+ `v` => abajo
	+ `#` => reiniciar
	+ `*` => continuar
1. Una vez iniciada la generación de silencio, solo puedes parar mediante el botón
	+ `#` => reiniciar

# Modos de silencio (Single-core)
+ silence_mode_1
+ silence_mode_2
+ silence_mode_3
+ silence_mode_4

# Tabla de conexiones

<table>
  <caption>Silence Machine - ESP32</caption>
  <thead>
    <tr>
      <th>Componente</th>
      <th>Especificación</th>
      <th>Pin (ESP32)</th>
      <th>10uf capacitor / 2da opción</th>
      <th>Cable</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>1st nRF24L01</td>
      <td>VCC 🔴</td>
      <td>3.3V</td>
      <td>N/A (+) capacitor</td>
      <td>Rojo</td>
    </tr>
    <tr>
      <td>1st nRF24L01</td>
      <td>GND ⬛</td>
      <td>GND</td>
      <td>N/A (-) capacitor</td>
      <td>Negro</td>
    </tr>
    <tr>
      <td>1st nRF24L01</td>
      <td>CE 🟡</td>
      <td>GPIO 04</td>
      <td></td>
      <td>Amarillo</td>
    </tr>
    <tr>
      <td>1st nRF24L01</td>
      <td>CSN 🟠</td>
      <td>GPIO 05</td>
      <td></td>
      <td>Naranja</td>
    </tr>
    <tr>
      <td>1st nRF24L01</td>
      <td>SCK 🟢</td>
      <td>GPIO 18</td>
      <td></td>
      <td>Verde</td>
    </tr>
    <tr>
      <td>1st nRF24L01</td>
      <td>MOSI 🔵</td>
      <td>GPIO 23</td>
      <td></td>
      <td>Azul</td>
    </tr>
    <tr>
      <td>1st nRF24L01</td>
      <td>MISO 🟣</td>
      <td>GPIO 19</td>
      <td></td>
      <td>Morado</td>
    </tr>
    <tr>
      <td>1st nRF24L01</td>
      <td>IRQ</td>
      <td></td>
      <td></td>
      <td></td>
    </tr>
    <tr>
      <td>2do nRF24L01</td>
      <td>VCC 🔴</td>
      <td>3.3V</td>
      <td>N/A (+) capacitor</td>
      <td>Rojo</td>
    </tr>
    <tr>
      <td>2do nRF24L01</td>
      <td>GND ⬛</td>
      <td>GND</td>
      <td>N/A (-) capacitor</td>
      <td>Negro</td>
    </tr>
    <tr>
      <td>2do nRF24L01</td>
      <td>CE 🟡</td>
      <td>GPIO 02</td>
      <td></td>
      <td>Amarillo</td>
    </tr>
    <tr>
      <td>2do nRF24L01</td>
      <td>CSN 🟠</td>
      <td>GPIO 15</td>
      <td></td>
      <td>Naranja</td>
    </tr>
    <tr>
      <td>2do nRF24L01</td>
      <td>SCK 🟢</td>
      <td>GPIO 14</td>
      <td></td>
      <td>Verde</td>
    </tr>
    <tr>
      <td>2do nRF24L01</td>
      <td>MOSI 🔵</td>
      <td>GPIO 13</td>
      <td></td>
      <td>Azul</td>
    </tr>
    <tr>
      <td>2do nRF24L01</td>
      <td>MISO 🟣</td>
      <td>GPIO 12</td>
      <td></td>
      <td>Morado</td>
    </tr>
    <tr>
      <td>2do nRF24L01</td>
      <td>IRQ</td>
      <td></td>
      <td></td>
      <td></td>
    </tr>
    <tr>
      <td>Button 1 - UP</td>
      <td>Terminal</td>
      <td>GPIO 17</td>
      <td></td>
      <td></td>
    </tr>
    <tr>
      <td>Button 1 - UP</td>
      <td>Terminal</td>
      <td>GND</td>
      <td></td>
      <td></td>
    </tr>
    <tr>
      <td>Button 2 - DOWN</td>
      <td>Terminal</td>
      <td>GPIO 16</td>
      <td></td>
      <td></td>
    </tr>
    <tr>
      <td>Button 2 - DOWN</td>
      <td>Terminal</td>
      <td>GND</td>
      <td></td>
      <td></td>
    </tr>
    <tr>
      <td>Button 3 - #</td>
      <td>Terminal</td>
      <td>EN</td>
      <td></td>
      <td></td>
    </tr>
    <tr>
      <td>Button 3 - #</td>
      <td>Terminal</td>
      <td>GND</td>
      <td></td>
      <td></td>
    </tr>
    <tr>
      <td>Button 4 - *</td>
      <td>Terminal</td>
      <td>GPIO 26</td>
      <td></td>
      <td></td>
    </tr>
    <tr>
      <td>Button 4 - *</td>
      <td>Terminal</td>
      <td>GND</td>
      <td></td>
      <td></td>
    </tr>
    <tr>
      <td>Display 1</td>
      <td>VCC 🔴</td>
      <td>3.3V</td>
      <td></td>
      <td>Rojo</td>
    </tr>
    <tr>
      <td>Display 1</td>
      <td>GND ⬛</td>
      <td>GND</td>
      <td></td>
      <td>Negro</td>
    </tr>
    <tr>
      <td>Display 1</td>
      <td>SDA 🟡</td>
      <td>GPIO 21</td>
      <td>GPIO 32</td>
      <td>Amarillo</td>
    </tr>
    <tr>
      <td>Display 1</td>
      <td>SCL 🟠</td>
      <td>GPIO 22</td>
      <td>GPIO 33</td>
      <td>Naranja</td>
    </tr>
  </tbody>
</table>

# El proyecto, desarrollo, colaboración y modos de silencio
Este proyecto es posible gracias a proyectos similares que eran Open Source. Este proyecto es Open Source y busca:
1. Ser fácil de leer, analizar y modificar
1. Permitir añadir modos de silencio personalizados
1. Ser lo más eficiente posible
	+ Durante el desarrollo de este proyecto se realizó un análisis y comparación de resultados, dando como resultado un proyecto más eficiente.
	+ En las próximas semanas publicaré el resultado de algunas comparativas. (Espera el link aquí)
