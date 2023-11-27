/*Тест маскировки под LLS датчики уровня топлива*/

uint8_t packLLS[10]; //отправлять пакет
uint8_t crc;
void setup() {
  Serial.begin(115200);

}

void sendPack(){
packLLS[0] = 0x3E;//Префикс
packLLS[1] = 0x01;//Сетевой адрес отправителя 
packLLS[2] = 0x06;//Код операции 
packLLS[3] = random(0,255);//Температура в градусах Цельсия 
packLLS[4] = random(0,16);
packLLS[5] = random(0,255);
packLLS[6] = 0x00;
packLLS[7] = 0x00;

crc = 0x00;//Обнуление
for(int i = 0; i < sizeof(packLLS)-2; i++) 
{
  crc = CRC8(packLLS[i], crc);
}

packLLS[8] = crc;

//выводим данные из массива
for (byte i = 0; i < sizeof(packLLS)-1; i++){
 //Serial.print(" 0x");
 Serial.print(packLLS[i], HEX);
}
Serial.println();
delay(3000);

}

void loop() {
  sendPack();
}

uint8_t CRC8 (uint8_t b, uint8_t crc)
{
uint8_t i = 8;
do {
  if ( (b ^ crc) & 0x01) {
  crc = ( (crc ^ 0x18) >> 1 ) | 0x80;
  } else {
  crc >>= 1;
  }
  b >>= 1;
  } while (--i);
  return crc;
}

/*
U8 CRC8 (U8 b, U8 crc)
{
U8 i = 8;
do {
if ( (b ^ crc) & 0x01) {
crc = ( (crc ^ 0x18) >> 1 ) | 0x80;
} else {
crc >>= 1;
}
b >>= 1;
} while (--i);
return crc;
}
*/
