import sys

def hamming74(data_bits):
    """Aplica código de Hamming (7,4) para 4 bits."""
    d = [int(bit) for bit in data_bits]
    p1 = d[0] ^ d[1] ^ d[3]
    p2 = d[0] ^ d[2] ^ d[3]
    p3 = d[1] ^ d[2] ^ d[3]
    return f"{p1}{p2}{d[0]}{p3}{d[1]}{d[2]}{d[3]}"

def aplicar_hamming(payload):
    """Aplica o código de Hamming em blocos de 4 bits."""
    if len(payload) % 4 != 0:
        payload += '0' * (4 - len(payload) % 4)  # padding

    resultado = ""
    for i in range(0, len(payload), 4):
        bloco = payload[i:i+4]
        resultado += hamming74(bloco)
    return resultado

def montar_frame(bits_codificados):
    CABECALHO = "01111110"
    TERMINADOR = "01111110"
    return f"{CABECALHO}{bits_codificados}{TERMINADOR}"

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Uso: python remetente.py <bits>")
        sys.exit(1)

    entrada_bits = sys.argv[1]
    bits_codificados = aplicar_hamming(entrada_bits)
    frame = montar_frame(bits_codificados)
    print(frame)
