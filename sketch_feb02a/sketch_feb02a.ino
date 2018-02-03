/*
 按键去抖

每当输入引脚发生高低电平的变化时(比如由于矩阵按键被按下了)，或当输出引脚发生高低电平的变化时，程序就应该暂停一小段时间来避免这个抖动的干扰（或者说避免这种电子噪声的干扰）。


 电路搭建:
 * LED连接13号引脚和GND
 * 矩阵按键连接2号引脚和+5V
 * 10kΩ电阻连接2号引脚和GND

 * 小贴士: 大多数Arduino板在13号引脚已经有板载LED，所以你一般不用附加LED来完成本例。

 代码是公开的
 */

// 常量，用来定义引脚号码
const int buttonPin = 2;    // 连接矩阵按键的引脚
const int ledPin = 13;      // LED引脚

// 变量的声明与定义:
int ledState = HIGH;         // 记录LED的状态
int buttonState;             // 记录按键的状态
int lastButtonState = LOW;   // 上一次按键的状态

// 以下代码以long类型声明，因为时间值以毫秒为单位(用整型会很快溢出)
long lastDebounceTime = 0;  // 按键最后一次被触发
long debounceDelay = 50;    // 为了滤去抖动暂停的时间，如果发现输出不正常增加这个值

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // 设置LED初始状态
  digitalWrite(ledPin, ledState);
}

void loop() {
  // 读取按键状态并存储到变量中:
  int reading = digitalRead(buttonPin);

  // 检查下按键状态是否改变(换句话说，输入是否是从LOW到HIGH)。
  // 检查是否距离上一次按下的时间已经足够滤去按键抖动:

  // 如果按键状态和上次不同:
  if (reading != lastButtonState) {
    // 记录初始时间
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // 离初始时间已经过了按键抖动出现的时间，因此当前的按键状态是稳定状态:

    // 如果按键状态改变了:
    if (reading != buttonState) {
      buttonState = reading;

      // 只有当稳定的按键状态时HIGH时才打开LED。
      if (buttonState == HIGH) {
        ledState = !ledState;
        Serial.write("1");
      }
    }
  }

  // 设置LED:
  digitalWrite(ledPin, ledState);

  // 保存处理结果:
  lastButtonState = reading;
}
