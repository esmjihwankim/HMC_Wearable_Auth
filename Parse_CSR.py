import re
from OpenSSL import crypto
from cryptography.hazmat.primitives import serialization
from cryptography.hazmat.primitives.asymmetric import rsa
from cryptography.hazmat.primitives.asymmetric import ec
import base64


sample_str = """-----BEGIN CERTIFICATE REQUEST-----
Subject: CN=hyundai_research.com, C=KO
Public Key: SNR2BkH8XmtQyUAKr2KRngdzi+vZ+GbocyKIORNxhjssI534susUUH5zMM2KP/cAlOjAi8NQLorSyaHoHhSD2w==
-----END CERTIFICATE REQUEST-----"""

def parse_custom_csr(csr_str):
    # CSR 문자열에서 필요한 정보 추출
    subject_match = re.search(r'Subject: (.+)', csr_str)
    pubkey_match = re.search(r'Public Key: (.+)', csr_str)

    print("Parse_CSR_LOG1::", subject_match, pubkey_match)

    if not subject_match or not pubkey_match:
        raise ValueError("Invalid CSR format")

    subject_str = subject_match.group(1)
    pubkey_str = pubkey_match.group(1)

    print("Parse_CSR_LOG2:: ", subject_str, pubkey_str)

    # Subject 파싱
    subject = crypto.X509Req().get_subject()
    for part in subject_str.split(', '):
        key, value = part.split('=')
        setattr(subject, key, value)

    # Public Key 파싱
    pubkey_bytes = base64.b64decode(pubkey_str)
    if pubkey_bytes[0] != 0x04:
        pubkey_bytes = b'\x04' + pubkey_bytes

    try:
        pubkey = ec.EllipticCurvePublicKey.from_encoded_point(ec.SECP256R1(), pubkey_bytes)

        pem_pubkey = pubkey.public_bytes(
            encoding=serialization.Encoding.PEM,
            format=serialization.PublicFormat.SubjectPublicKeyInfo
        )
        pkey = crypto.load_publickey(crypto.FILETYPE_PEM, pem_pubkey)
        print("Parse_CSR_LOG3::public key loaded successfully::", pubkey.public_numbers())


    except ValueError as e:
        print(f"Parse_CSR_LOG4::Public key loading error:: {e}")

    return subject, pkey


if __name__ == "__main__":
    subject, key = parse_custom_csr(sample_str)
    print(subject.get_components())
    print(key)

