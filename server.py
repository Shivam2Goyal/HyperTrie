import os
from flask import Flask, request, jsonify
from flask_cors import CORS, cross_origin

app = Flask(__name__)
CORS(app)

@app.route('/store_url', methods=['POST'])
@cross_origin()
def store_url():
    data = request.get_json()
    if 'url' in data:
        url = data['url']
        print(f"Received URL: {url}")

        # Get the absolute path to the urls.txt file
        app_root = os.path.dirname(os.path.abspath(__file__))
        urls_txt_path = os.path.join(app_root, 'urls.txt')

        try:
            with open(urls_txt_path, 'a') as file:
                file.write(url + '\n')
            print(f"URL {url} stored successfully.")
        except Exception as e:
            print(f"Error storing URL {url}: {e}")
            return jsonify({"error": "Error storing URL"}), 500

        return jsonify({"message": f"URL {url} stored"}), 200
    return jsonify({"error": "No URL provided"}), 400

if __name__ == '__main__':
    app.run(debug=True)