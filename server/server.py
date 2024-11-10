# server/server.py
import os
from flask import Flask, request, jsonify
from flask_cors import CORS, cross_origin
from collections import Counter

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

@app.route('/get_history', methods=['GET'])
@cross_origin()
def get_history():
    try:
        app_root = os.path.dirname(os.path.abspath(__file__))
        urls_txt_path = os.path.join(app_root, 'urls.txt')
        
        with open(urls_txt_path, 'r') as file:
            urls = [line.strip() for line in file if line.strip()]
        
        # Count occurrences of each URL
        url_counts = Counter(urls)
        
        # Format for frontend
        history = [{"url": url, "visits": count} 
                  for url, count in url_counts.items()]
        
        return jsonify(history), 200
    except Exception as e:
        return jsonify({"error": str(e)}), 500

if __name__ == '__main__':
    app.run(debug=True)