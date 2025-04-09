# 🛰️ Comunicação na Camada de Enlace com Código de Hamming (7,4)

Este projeto implementa uma simulação da camada de enlace de redes utilizando o **Código de Hamming (7,4)** para detecção e correção de erro de 1 bit. A comunicação pode ser feita via **pipes** com Python ou via **sockets TCP** com C.

---

## 📂 Estrutura do Projeto

```
modulo9-p3/
├── remetente.py       # Codifica bits com Hamming e monta frame
├── destinatario.py    # Lê frame, corrige erro e decodifica mensagem
├── server.c           # Servidor em C que recebe frames via socket
├── client.c           # Cliente em C que envia arquivos via socket
├── build.bat          # Script de compilação automática
├── dados.txt          # Exemplo de arquivo com frame
└── README.md          # Documentação do projeto
```

---

## 🧪 Como testar com Python (pipes)

### Gerar e enviar o frame

```bash
python remetente.py 01101001 > dados.txt
type dados.txt | python destinatario.py
```

Saída esperada:

```
Mensagem original: 01101001
```

---

## 🌐 Como testar com Sockets TCP (cliente-servidor)

### 1. Compile os programas em C  
Execute o script de build:

```bash
.\build.bat
```

### 2. Inicie o servidor  
Em um terminal:

```bash
.\server.exe
```

### 3. Gere um frame com remetente.py

```bash
python remetente.py 01101001 > dados.txt
```

### 4. Envie o frame com o cliente  
Em outro terminal:

```bash
.\client.exe dados.txt
```

O servidor imprimirá o conteúdo recebido no console.

---

## 🧠 Lógica dos Frames

Cada frame enviado possui:

- **Cabeçalho:** `01111110`
- **Payload:** bits codificados com Hamming
- **Terminador:** `01111110`

---

## 🔎 Código de Hamming (7,4)

Cada grupo de 4 bits é convertido em 7 bits com 3 bits de paridade, permitindo detecção e correção de 1 bit de erro.

---

## ✅ Requisitos

- Python 3.x  
- MinGW-W64 com suporte a `-lws2_32`, `-lpthread`, etc.  
- Windows PowerShell ou CMD
