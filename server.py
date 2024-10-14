from flask import Flask, request, jsonify
from flask_cors import CORS

app = Flask(__name__)
CORS(app)  # Enables CORS for all routes

@app.route('/store_url', methods=['POST'])
def store_url():
    data = request.get_json()
    if 'url' in data:
        url = data['url']
        print(f"Received URL: {url}")
        return jsonify({"message": f"URL {url} stored"}), 200
    return jsonify({"error": "No URL provided"}), 400

if __name__ == '__main__':
    app.run(debug=True)
