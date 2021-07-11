SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);


os_thread_t thread1;
os_thread_t thread2;
os_thread_t thread3;

os_mutex_t mutex;

int printTwo = 0;

void myThread1(void *args) {
  while (1) {
    // your code here
    int printOne = rand() % 100;
    WITH_LOCK(Serial) {
    // your serial port code code here
      Serial.print("Thread 1: ");
      Serial.println(printOne);
    }
    delay(1000);
  }
}

void myThread2(void *args) {
  while (1) {
    Serial.print("Thread 2: ");
    printTwo++;
    WITH_LOCK(Serial) {
    // your serial port code code here
      Serial.println(printTwo);
    }
    delay(500);

  }
}

void myThread3(void *args) {
  while (1) {
    // your code here
    digitalWrite(D7, !(digitalRead(D7)));
    delay(125);
  }
}



// setup() runs once, when the device is first turned on.
void setup() {
  // Put initialization like pinMode and begin functions here.
  pinMode(D7, OUTPUT);
  pinMode(D3, OUTPUT);

  os_thread_create(&thread1, "Random number", OS_THREAD_PRIORITY_DEFAULT, myThread1, NULL, 1024);
  os_thread_create(&thread2, "Increment value", OS_THREAD_PRIORITY_DEFAULT, myThread2, NULL, 1024);
  os_thread_create(&thread3, "Flash", OS_THREAD_PRIORITY_DEFAULT, myThread3, NULL, 1024);
  Serial.begin(9600);
  while (!Serial.isConnected());

}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.

}

