from flask import Flask, request, jsonify
from OpenSSL import crypto
import cryptography
import os
import base64
import datetime
import re
import Parse_CSR

app = Flask(__name__)

ROOT_CA_CERT = "./key+cert/rootCA.pem"
ROOT_CA_KEY = "./key+cert/rootCA.key"
INTERMEDIATE_CA_CERT = "./key+cert/intermediateCA.pem"
INTERMEDIATE_CA_KEY = "./key+cert/intermediateCA.key"

signed_certificate = bytearray()

# Load IntermediateCA Cert and Key
with open(INTERMEDIATE_CA_CERT, "rb") as f:
    intermediate_ca_cert = crypto.load_certificate(crypto.FILETYPE_PEM, f.read())

with open(INTERMEDIATE_CA_KEY, "rb") as f:
    ca_key = crypto.load_privatekey(crypto.FILETYPE_PEM, f.read())

with open(ROOT_CA_CERT, "rb") as f:
    root_ca_cert = crypto.load_certificate(crypto.FILETYPE_PEM, f.read())


# main
@app.route('/')
def index():
    return "Hyundai Motors Digital Key System"


# end point receiving CSR
@app.route('/test')
def test():
    return "test page"

@app.route('/intermediateCA_cert', methods=['POST'])
def send_intermediate_certificate():
    with open(INTERMEDIATE_CA_CERT, 'r') as cert_file:
        cert_data = cert_file.read()
    print("MAIN_LOG::Intermed Cert:: Cert loaded and ready to be sent")
    return jsonify({"certificate": cert_data}), 200


# end point receiving CSR
@app.route('/csr', methods=['POST'])
def sign_csr_for_iOS():
    csr_str = request.data.decode('utf-8')
    if not csr_str:
        return jsonify({"error": "No CSR provided"}), 400

    print("MAIN_LOG::Handling CSR::CSR_pem:: ", csr_str)

    try:
        subject, pubkey = Parse_CSR.parse_custom_csr(csr_str)

        # 새 인증서 생성
        cert = crypto.X509()
        cert.set_subject(subject)
        cert.set_serial_number(1000)
        cert.gmtime_adj_notBefore(0)
        cert.gmtime_adj_notAfter(365 * 24 * 60 * 60)  # valid for 1 year
        cert.set_issuer(intermediate_ca_cert.get_subject())
        cert.set_pubkey(pubkey)

        cert.sign(ca_key, 'sha256')
        print("MAIN_LOG::Certificate Signed Successfully")
        print(cert)
        signed_certificate = crypto.dump_certificate(crypto.FILETYPE_PEM, cert).decode('utf-8')
        return jsonify({"certificate": signed_certificate}), 200

    except Exception as e:
        print("MAIN_LOG::Exception occurred: ", e)
        return jsonify({"error": str(e)}), 500




if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0')
