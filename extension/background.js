chrome.tabs.onUpdated.addListener(async (tabId, changeInfo, tab) => {
    if (changeInfo.url) {
      try {
        const response = await fetch('http://127.0.0.1:5000/store_url', {
          method: 'POST',
          headers: {
            'Content-Type': 'application/json'
          },
          body: JSON.stringify({ url: changeInfo.url })
        });
  
        if (!response.ok) {
          throw new Error(`HTTP error ${response.status}`);
        }
  
        const data = await response.json();
        console.log('URL Sent:', data);
      } catch (error) {
        console.error('Error sending URL:', error);
      }
    }
  });