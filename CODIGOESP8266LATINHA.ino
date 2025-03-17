#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

// Configuração do Wi-Fi
const char* ssid = "Uniamerica_Colaboradores";
const char* password = "";

// Configuração do Firebase
#define FIREBASE_HOST "https://contadorlatinhas-default-rtdb.firebaseio.com"
#define API_KEY "AIzaSyAe-o1t33zQ0La8ekPjKcalwXXq_SIh2gI"

#define USER_EMAIL "miguelggarbo@gmail.com"
#define USER_PASSWORD "Minecraft1308#"

FirebaseData firebaseData;
FirebaseAuth auth;
FirebaseConfig config;

int totalLatinhas = 0;

void setup() {
    Serial.begin(115200);  // Comunicação Serial com ATmega328
    WiFi.begin(ssid, password);

    Serial.print("Conectando ao WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }

    Serial.println("\n✅ WiFi Conectado!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());

    // Configuração do Firebase
    config.host = FIREBASE_HOST;
    config.api_key = API_KEY;

    // Autenticação com e-mail e senha
    auth.user.email = USER_EMAIL;
    auth.user.password = USER_PASSWORD;

    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);

    Serial.println("🔥 Firebase conectado!");
}

void loop() {
    // Se houver dados na Serial (vindo do ATmega328)
    if (Serial.available() > 0) {
        totalLatinhas = Serial.parseInt(); // Lê um número inteiro
        Serial.print("📩 Dado recebido: ");
        Serial.println(totalLatinhas);

        // Enviar para o Firebase
        if (Firebase.setInt(firebaseData, "/Quantidadelata", totalLatinhas)) {
            Serial.println("✅ Dados enviados para o Firebase!");
        } else {
            Serial.print("❌ Erro ao enviar: ");
            Serial.println(firebaseData.errorReason()); // Mensagem detalhada do erro
        }
    }

    delay(1000); // Pequena pausa para evitar excesso de requisições
}
