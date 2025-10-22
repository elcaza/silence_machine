/*
* Silence Machine - Single Core v1 
* https://github.com/elcaza/silence_machine_single_core
* elcaza
* ESP32
*/

#include <SPI.h>
#include "RF24.h"
#include <ezButton.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// =====================================================================
// INICIO DE OPCIONES CONFIGURABLES
// Opciones relacionadas al cableado
// =====================================================================

// ****************************************************
// CONFIGURACION DE PANTALLA (I2C)
// ****************************************************

// SDA va al GPIO 21 || también puede ser 32
// SCL va al GPIO 22 || también puede ser 33
#define SDA_PIN 32
#define SCL_PIN 33

// Tamaño de pantalla en pixeles
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
// Dirección I2C del OLED. Los valores comunes son 0x3C o 0x3D.
#define OLED_ADDR 0x3C

// ****************************************************
// CONFIGURACION DE RADIOS (DUAL-SPI)
// ****************************************************

// Pines de control para la RADIO 1 1 (VSPI, controlador 1)
// No se deben cambiar: CSN1_PIN, SCK1_PIN, MISO1_PIN MOSI1_PIN
// Estas son las usadas por defecto por el SPI
#define CE1_PIN 4
#define CSN1_PIN 5
#define SCK1_PIN 18
#define MISO1_PIN 19
#define MOSI1_PIN 23

// Pines de control para la RADIO 2 (HSPI, controlador 2)
// Aquí sí puedes cambiar las que gustes
#define CE2_PIN 2
#define CSN2_PIN 15
#define SCK2_PIN 14
#define MISO2_PIN 12
#define MOSI2_PIN 13

// ****************************************************
// CONFIGURACION BOTONES
// ****************************************************
const int BUTTON_PIN1 = 16; // UP - K1
const int BUTTON_PIN2 = 17; // DOWN - K2
const int BUTTON_PIN4 = 26; // * START - K4
// BUTTON_3 TO EN (Reset físico)
const int debounce_time = 100;

// ****************************************************
// CONFIGURACIONES ADICIONALES
// ****************************************************

const long SERIAL_BAUD = 115200;

// Se encuentran en CH
const int wifi_frequencies[] = {
	// 2412, 2417, 2422, 2427, 2432, 2437, 2442, 2447, 2452, 2457, 2462
	12, 17, 22, 27, 32, 37, 42, 47, 52, 57, 62
};

byte byte_i = 45;

// =====================================================================
// FIN DE OPCIONES CONFIGURABLES
// =====================================================================

// ****************************************************
// Variables para radios
// ****************************************************

// El primer SPI usa la variable por default
SPIClass spi2(HSPI);
RF24 radio1(CE1_PIN, CSN1_PIN); // VSPI
RF24 radio2(CE2_PIN, CSN2_PIN); // HSPI

// ****************************************************
// Variables para botones, display y modo de silencio
// ****************************************************

ezButton button1(BUTTON_PIN1); // UP - K1
ezButton button2(BUTTON_PIN2); // DOWN - K2
ezButton button4(BUTTON_PIN4); // * START - K4

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire);

bool oled_success = false;
bool rf1_success = false;
bool rf2_success = false;

char string_current_index[10];
char string_number_of_modes[10];

// =====================================================================
// INICIO DE OPCIONES CONFIGURABLES
// Configuración de los modos de silencio
// Debe coincidir:
// # modos en el array = # funciones = # de opciones en el menú
// =====================================================================

// ****************************************************
// Descripción para los modos de silencio. El modo es su indice.
// ****************************************************

const char* all_modes[] = {
	"Description for mode 1",
	"Description for mode 2",
	"Description for mode 3",
	"Description for mode 4"
};

int number_of_modes = sizeof(all_modes) / sizeof(all_modes[0]);

// ****************************************************
// Funciones de los modos de silencio
// ****************************************************

// Modos de silencio, funciones.
void silence_mode_1() {
	while(1){
		for (size_t i = 0; i < 40; i++) {
			radio1.setChannel(i);
			radio2.setChannel(i+40);
		}
	}
}

void silence_mode_2() {
	while(1){
		for (size_t i = 0; i < 37; i++) {
			radio1.setChannel(i);
			radio2.setChannel(i+40);

			radio1.setChannel(i+3);
			radio2.setChannel(i+43);
		}
	}
}

void silence_mode_3() {
	while(1){
		for (size_t i = 0; i < 78; i++) {
			radio1.setChannel(i);
			radio2.setChannel(i+2);
		}
	}
}

void silence_mode_4() {
	while(1){
		for (size_t i = 0; i < sizeof(wifi_frequencies) / sizeof(wifi_frequencies[0]); i++) {
			radio1.setChannel(wifi_frequencies[i]);
			radio2.setChannel(wifi_frequencies[i]+2);
		}
	}
}

// ****************************************************
// Menú para los modos de silencio
// ****************************************************

// Modos de silencio, función inicializadora.
void generate_silence(int p_index) {
	switch (p_index + 1) {
		case 1:
			Serial.println(F("Case 1"));
			silence_mode_1();
			break;
		case 2:
			Serial.println(F("Case 2"));
			silence_mode_2();
			break;
		case 3:
			Serial.println(F("Case 3"));
			silence_mode_3();
			break;
		case 4:
			Serial.println(F("Case 4"));
			silence_mode_4();
			break;
		default:
			Serial.println(F("Ocurrio un error en la funcion generate_silenc"));
			break;
	}
}

// =====================================================================
// FIN DE OPCIONES CONFIGURABLES
// =====================================================================

// ****************************************************
// Funciones que muestran opciones en pantalla
// ****************************************************

void show_health_test(bool p_oled_ok, bool p_rf1_ok, bool p_rf2_ok) {
	display.clearDisplay();
	display.setTextSize(1);
	display.setTextColor(WHITE);

	display.setCursor(0, 0);
	display.println("Silence Machine v1");

	display.setCursor(0, 10);
	display.println("Single core version");

	display.setCursor(0, 25);
	display.print("OLED: ");
	display.println(p_oled_ok ? "OK" : "ERROR");

	display.setCursor(0, 35);
	display.print("RF 1: ");
	display.println(p_rf1_ok ? "OK" : "ERROR");
		
	display.setCursor(0, 45);
	display.print("RF 2: ");
	display.println(p_rf2_ok ? "OK" : "ERROR");

	display.setCursor(0, 57);
	display.print("Press # Reset * Start");
	
	display.display();
}

void show_nav(const char* p_current_mode, const char* p_available_modes) {
	display.clearDisplay();
	display.setTextSize(1);

	// Arriba
	display.setRotation(3);
	display.setCursor(56, 120);
	display.print(">");

	// Abajo
	display.setCursor(37, 120);
	display.print("<");
	
	display.setRotation(0);
	display.setCursor(122, 40);
	display.print("#");

	display.setCursor(122, 56);
	display.print("*");

	display.setCursor(0, 0);
	display.println("Silence mode:\n");
	display.setTextSize(2);
	display.print(p_current_mode);
	display.print(" / ");
	display.println(p_available_modes);
	display.setTextSize(1);
	display.println("");
	display.println(all_modes[atoi(p_current_mode)-1]);
	display.display();
}

void show_current_mode(int p_mode){
	display.clearDisplay();
	display.setTextSize(1);
	display.setTextColor(WHITE);

	display.setCursor(0, 0);
	display.print("Silence mode: ");
	display.println(p_mode);

	display.setCursor(0, 45);
	display.println("Reboot system => #");
	
	display.display();
}

// ****************************************************
// Funciones de menu
// ****************************************************

void press_to_start(){
	bool waiting_menu = true;

	while(waiting_menu) {
		button4.loop();

		if (button4.isPressed()) {
			// Se presionó '*' para continuar	
			waiting_menu = false;
		}
		
		// Delay para evitar saturar el núcleo con el bucle
		delay(5);
	}
}

void start_nav() {
	bool waiting_menu = true;
	int current_index = 0;
	bool nav_changed = false;

	itoa(current_index + 1, string_current_index, 10); 
	itoa(number_of_modes, string_number_of_modes, 10);
	show_nav(string_current_index, string_number_of_modes);

	while(waiting_menu) {
		button1.loop();
		button2.loop();
		button4.loop();

		if (button1.isPressed()) {
			if (current_index > 0) {
				current_index--;
				nav_changed = true;
			}
		}

		if (button2.isPressed()) {
			if (current_index < number_of_modes-1) {
				current_index++;
				nav_changed = true;
			}
		}

		if (nav_changed) {
			itoa(current_index + 1, string_current_index, 10); 
			show_nav(string_current_index, string_number_of_modes);
			nav_changed = false;
			// Serial.printf("Indice: %d, Muestra: %s / %s\n", current_index, string_current_index, string_number_of_modes);
		}

		if (button4.isPressed()) {
			show_current_mode(current_index+1);
			generate_silence(current_index);
		}
		// Delay para evitar saturar el núcleo con el bucle
		delay(5);
	}
}

// ****************************************************
// Setup y loop
// ****************************************************

void setup() {
	// Conexión Serial
	Serial.begin(SERIAL_BAUD);
	Serial.println(F("Silence Machine v1 - Single core version")); 

	// Inicialización de los botones
	button1.setDebounceTime(debounce_time);
	button2.setDebounceTime(debounce_time);
	button4.setDebounceTime(debounce_time);
	
	pinMode(BUTTON_PIN1, INPUT_PULLUP); 
	pinMode(BUTTON_PIN2, INPUT_PULLUP); 
	pinMode(BUTTON_PIN4, INPUT_PULLUP); 
	
	// Inicialización de la pantalla
	Wire.begin(SDA_PIN, SCL_PIN); 
	if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
		Serial.println(F("ERROR: OLED screen not found!"));
		Serial.println(F("Te recomendamos utilizar la siguiente herramienta para ver si todas las conexiones estan bien"));
		Serial.println(F("https://github.com/elcaza/jammon_tester"));
		while(1);
	}
	oled_success = true;
	
	// Inicialización de los módulos RF
	// Radio 1 usa el SPI por defecto
	if (radio1.begin()) {
		radio1.setAutoAck(false); 
		radio1.stopListening();
		radio1.setRetries(0, 0);
		radio1.setPayloadSize(5);
		radio1.setAddressWidth(3);
		radio1.setPALevel(RF24_PA_MAX);
		radio1.setDataRate(RF24_2MBPS);
		radio1.setCRCLength(RF24_CRC_DISABLED);
		// radio1.printPrettyDetails();
		radio1.startConstCarrier(RF24_PA_MAX, byte_i);
		Serial.println(F("RADIO 1 - OK"));
		rf1_success = true;
	} else {
		Serial.println(F("Error al iniciar Radio 1"));
	}

	spi2.begin(SCK2_PIN, MISO2_PIN, MOSI2_PIN, CSN2_PIN);

	if (radio2.begin(&spi2)) { 
		radio2.setAutoAck(false); 
		radio2.stopListening();
		radio2.setRetries(0, 0);
		radio2.setPayloadSize(5);
		radio2.setAddressWidth(3);
		radio2.setPALevel(RF24_PA_MAX);
		radio2.setDataRate(RF24_2MBPS);
		radio2.setCRCLength(RF24_CRC_DISABLED);
		// radio2.printPrettyDetails();
		radio2.startConstCarrier(RF24_PA_MAX, byte_i);
		Serial.println(F("RADIO 2 - OK"));
		rf2_success = true;
	} else {
		Serial.println(F("Error al iniciar RADIO 2"));
	}

	show_health_test(oled_success, rf1_success, rf2_success);

	press_to_start();
	
	start_nav();
}

void loop() {

}