from OpenSSL import crypto
from cryptography.hazmat.primitives.asymmetric import ec
import base64

# test ------------------------------------------------------------------------
pkey_str = "SNR2BkH8XmtQyUAKr2KRngdzi+vZ+GbocyKIORNxhjssI534susUUH5zMM2KP/cAlOjAi8NQLorSyaHoHhSD2w=="
pkey_bytes = base64.b64decode(pkey_str)
if pkey_bytes[0] != 0x04:
    pkey_bytes = b'\x04' + pkey_bytes
try:
    pubkey = ec.EllipticCurvePublicKey.from_encoded_point(ec.SECP256R1(), pkey_bytes)
    print("public key loaded successfully")
    print(pubkey.public_numbers())
except ValueError as e:
    print(f"Error loading public key: {e}")
# -----------------------------------------------------------------------------
