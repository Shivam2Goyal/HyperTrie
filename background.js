chrome.tabs.onUpdated.addListener((tabId, changeInfo, tab) => {
  if (changeInfo.url) {
      fetch('http://127.0.0.1:5000/store_url', {  // Flask server URL
          method: 'POST',
          headers: {
              'Content-Type': 'application/json'
          },
          body: JSON.stringify({ url: changeInfo.url })  // Send the URL in JSON format
      })
      .then(response => response.json())
      .then(data => console.log('URL Sent:', data))
      .catch(error => console.error('Error sending URL:', error));
  }
});
