import sys

def corrigir_hamming74(bits):
    """Corrige um bloco de 7 bits usando Hamming (7,4) e retorna os 4 bits de dados."""
    b = [int(bit) for bit in bits]
    # Paridades
    p1 = b[0]
    p2 = b[1]
    d1 = b[2]
    p3 = b[3]
    d2 = b[4]
    d3 = b[5]
    d4 = b[6]

    # Recalcular as paridades
    s1 = p1 ^ d1 ^ d2 ^ d4
    s2 = p2 ^ d1 ^ d3 ^ d4
    s3 = p3 ^ d2 ^ d3 ^ d4

    erro_posicao = s1 * 1 + s2 * 2 + s3 * 4  # posição do bit com erro (1 a 7)

    if erro_posicao != 0:
        print(f"[!] Bit com erro na posição {erro_posicao}, corrigindo...")
        bits_corrigidos = list(bits)
        pos = erro_posicao - 1
        bits_corrigidos[pos] = '0' if bits_corrigidos[pos] == '1' else '1'
        b = [int(bit) for bit in bits_corrigidos]

    return f"{b[2]}{b[4]}{b[5]}{b[6]}"  # Apenas bits de dados

def extrair_payload(frame):
    CABECALHO = "01111110"
    TERMINADOR = "01111110"

    if not frame.startswith(CABECALHO) or not frame.endswith(TERMINADOR):
        raise ValueError("Frame inválido: delimitadores ausentes.")

    return frame[len(CABECALHO):-len(TERMINADOR)]

def decodificar_payload(payload_bits):
    dados = ""
    for i in range(0, len(payload_bits), 7):
        bloco = payload_bits[i:i+7]
        if len(bloco) == 7:
            dados += corrigir_hamming74(bloco)
    return dados

if __name__ == "__main__":
    frame = sys.stdin.read().strip()

    try:
        payload = extrair_payload(frame)
        mensagem_original = decodificar_payload(payload)
        print(f"Mensagem original: {mensagem_original}")
    except Exception as e:
        print(f"Erro: {e}")
