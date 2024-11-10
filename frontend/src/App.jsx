// frontend/src/App.jsx
import React, { useState, useEffect } from 'react';
import { Clock, ExternalLink, Search } from 'lucide-react';

const App = () => {
  const [history, setHistory] = useState([]);
  const [searchTerm, setSearchTerm] = useState('');
  const [sortBy, setSortBy] = useState('visits');

  useEffect(() => {
    // Fetch history from your Python server
    fetch('http://127.0.0.1:5000/get_history')
      .then(response => response.json())
      .then(data => setHistory(data))
      .catch(error => console.error('Error fetching history:', error));
  }, []);

  const formatUrl = (url) => {
    try {
      const urlObj = new URL(url);
      return {
        domain: urlObj.hostname.replace('www.', ''),
        favicon: `https://www.google.com/s2/favicons?domain=${urlObj.hostname}`,
        fullUrl: url
      };
    } catch {
      return {
        domain: url,
        favicon: null,
        fullUrl: url
      };
    }
  };

  const filteredHistory = history
    .filter(item => 
      item.url.toLowerCase().includes(searchTerm.toLowerCase())
    )
    .sort((a, b) => {
      if (sortBy === 'visits') {
        return b.visits - a.visits;
      }
      return a.url.localeCompare(b.url);
    });

  const getTimeColor = (visits) => {
    if (visits >= 5) return 'text-green-600';
    if (visits >= 3) return 'text-yellow-600';
    return 'text-blue-600';
  };

  return (
    <div className="min-h-screen bg-gray-100 p-8">
      <div className="max-w-4xl mx-auto bg-white rounded-lg shadow-lg">
        <div className="p-6">
          <div className="flex items-center justify-between mb-6">
            <h1 className="text-2xl font-bold">Browser History</h1>
            <Clock className="w-6 h-6 text-gray-500" />
          </div>
          
          <div className="flex gap-4 mb-6">
            <div className="relative flex-1">
              <Search className="absolute left-3 top-2.5 h-4 w-4 text-gray-500" />
              <input
                type="text"
                placeholder="Search history..."
                className="w-full pl-10 pr-4 py-2 border rounded-lg focus:outline-none focus:ring-2 focus:ring-blue-500"
                value={searchTerm}
                onChange={(e) => setSearchTerm(e.target.value)}
              />
            </div>
            <select
              className="px-4 py-2 border rounded-lg focus:outline-none focus:ring-2 focus:ring-blue-500"
              value={sortBy}
              onChange={(e) => setSortBy(e.target.value)}
            >
              <option value="visits">Sort by Visits</option>
              <option value="url">Sort by URL</option>
            </select>
          </div>

          <div className="space-y-4">
            {filteredHistory.map((item, index) => {
              const { domain, favicon, fullUrl } = formatUrl(item.url);
              return (
                <div
                  key={index}
                  className="flex items-center justify-between p-4 bg-gray-50 rounded-lg hover:bg-gray-100 transition-colors"
                >
                  <div className="flex items-center space-x-3 flex-1">
                    {favicon && (
                      <img
                        src={favicon}
                        alt={domain}
                        className="w-6 h-6"
                        onError={(e) => e.target.style.display = 'none'}
                      />
                    )}
                    <div className="flex-1">
                      <div className="font-medium">{domain}</div>
                      <div className="text-sm text-gray-500 truncate">{fullUrl}</div>
                    </div>
                  </div>
                  <div className="flex items-center space-x-4">
                    <span className={`${getTimeColor(item.visits)} font-medium`}>
                      {item.visits} visits
                    </span>
                    <a
                      href={fullUrl}
                      target="_blank"
                      rel="noopener noreferrer"
                      className="text-gray-500 hover:text-gray-700"
                    >
                      <ExternalLink className="w-5 h-5" />
                    </a>
                  </div>
                </div>
              );
            })}
          </div>
        </div>
      </div>
    </div>
  );
};

export default App;