# 🌊 OverFlowen: Sistema de Prevenção de Alagamentos Residenciais

Este projeto foi desenvolvido como possível solução para um problema real relacionado às enchentes.
Projeto realizado para o Global Sotution da matéria Edge Computing & Computer Sistems do curso de Engenharia de Software da FIAP.

## 🔗 Links

Você pode visualizar o projeto no Wokwi e no YouTube pelos links abaixo:

👉 [Visualizar Projeto no Wokwi](https://wokwi.com/projects/432846681622453249)

📺 [Visualizar Explicação do Projeto no YouTube](https://youtu.be/1Rykeh_i0nM)

## 🙋‍♂️ Equipe

- [Pedro Faleiros](https://github.com/pedrofaleirosss)
- [Luan Felix](https://github.com/luansfff)
- [João Lopes](https://github.com/Joaolopes1311)

## 📌 Descrição

**OverFlowen** é um sistema de monitoramento e resposta rápida contra alagamentos residenciais. Utiliza sensores para medir o nível da água em tempo real e aciona alertas visuais, sonoros e uma barreira física automática para proteger ambientes internos da casa.

## 🏠 Problema

Alagamentos causados por chuvas intensas ou retorno da água de esgoto são comuns em diversas regiões urbanas. Eles trazem prejuízos materiais, riscos à saúde e perda de documentos e bens pessoais. A detecção precoce e uma resposta automática são cruciais para minimizar esses danos.

## ✅ Solução Proposta

Este sistema mede constantemente a distância entre o sensor e a superfície da água. Conforme a água sobe, o sistema:

- **Atualiza informações em tempo real no display LCD**;
- **Aciona LEDs coloridos** indicando o nível de risco (verde, amarelo, vermelho);
- **Emite som com buzzer** em situação crítica;
- **Fecha uma barreira automaticamente**, impedindo a entrada de água em cômodos;
- **Salva configurações personalizadas** na memória EEPROM.

## ⚙️ Componentes Utilizados

| Quantidade | Componente               |
|------------|--------------------------|
| 1          | Arduino Uno R3           |
| 1          | LCD 16x2 com I2C         |
| 1          | Sensor Ultrassônico HC-SR04 |
| 1          | Servo Motor|
| 1          | Buzzer                   |
| 3          | LEDs (verde, amarelo, vermelho) |
| 1          | Protoboard               |
| Vários     | Resistores (para Buzzer, LEDs) |
| Vários     | Cabos jumpers            |

## 🧠 Como Funciona

1. Ao iniciar, o sistema exibe uma animação de inicialização no LCD.
2. O sensor ultrassônico mede a distância da água até o sensor (instalado em uma parede ou ponto fixo).
3. Com base na altura configurada, calcula o nível de água em centímetros.
4. Exibe o nível da água no LCD juntamente com o status (OK, Alerta, Crítico).
5. Dependendo do nível:
   - **Baixo (OK)**: LED verde aceso.
   - **Médio (Alerta)**: LED amarelo e barreira fechada.
   - **Crítico (Risco de alagamento)**: LED vermelho, buzzer ativo, barreira fechada.
6. O usuário pode interagir via Serial Monitor para:
   - Alterar a altura do sensor;
   - Verificar o nível atual da água;
   - Exibir o menu de opções.

## ✨ Imagens do Projeto

![image](https://github.com/user-attachments/assets/db592698-7abb-4ed9-adcd-7c2f118d00e9)
![image](https://github.com/user-attachments/assets/985ccc7e-e554-449f-8a6d-ec7e71200201)
![image](https://github.com/user-attachments/assets/4fbc041f-f2fa-47dc-8672-773ca43ee6e6)
![image](https://github.com/user-attachments/assets/bf813c7d-f534-4ffc-b2f4-24659ce92503)
![image](https://github.com/user-attachments/assets/d6c90bf5-48fb-4f7e-bcbf-854d78ca4d5f)
![image](https://github.com/user-attachments/assets/de5f2c54-704c-4e9a-bbf3-3507a37895c8)
![image](https://github.com/user-attachments/assets/cc770b3f-b2c0-4969-bde7-db4fd03e3f47)

## 🛠️ Instalação

1. Conecte os componentes conforme o esquema.
2. Faça upload do código para o Arduino.
3. Acesse o Monitor Serial para configurar a altura do sensor.
4. Observe o LCD e os alertas conforme o nível da água simulado.
