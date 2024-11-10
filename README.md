# Efficient Browser History Tracker

This project is an efficient browser history tracker built using a custom Chrome extension, a Python server, a Trie-based C++ program, and a modern React frontend. The purpose is to capture, store, retrieve, and visualize browser history with optimized memory usage and quick access.

## Project Overview

This setup overcomes the limitations of traditional browser history storage by reducing redundancy and improving retrieval speed. It's especially useful for tracking frequently accessed sites, performing customized analysis on browsing data, and visualizing browsing patterns through an intuitive interface.


### How It Works

1. **Chrome Extension**: 
   - Captures each visited URL in real-time
   - Sends data to a local Python server
   - Works silently in the background while browsing

2. **Python Server**: 
   - Receives URLs from the Chrome extension
   - Appends them to `urls.txt`, creating a central log
   - Provides REST API endpoints for the frontend
   - Handles URL visit counting and data processing

3. **C++ Program**: 
   - Reads URLs from `urls.txt`
   - Stores each URL in a Trie data structure
   - Provides efficient tracking and retrieval
   - Monitors file changes in real-time

4. **React Frontend**:
   - Displays browser history in a modern, responsive UI
   - Provides search and sorting functionality
   - Shows visit counts and favicon for each URL
   - Updates in real-time as new URLs are visited

## Getting Started

### Prerequisites
- Node.js and npm
- Python 3.x
- C++ compiler
- Chrome browser

### Installation Steps

1. **Set up the Frontend**
```bash
# Navigate to frontend directory
cd frontend

# Install dependencies
npm install

# Start the development server
npm run dev
```

2. **Start the Python Server**
```bash
# Navigate to server directory
cd server

# Install required packages
pip install flask flask-cors

# Start the server
python server.py
```

3. **Compile and Run C++ Program**
```bash
# Navigate to cpp directory
cd cpp

# Compile the program
g++ -o history_tracker theOne.cpp

# Run the program
./history_tracker
```

4. **Load Chrome Extension**
- Open Chrome and go to `chrome://extensions/`
- Enable "Developer mode"
- Click "Load unpacked" and select the `extension` directory

### Usage
1. Once all components are running, the system will automatically track your browsing history
2. Access the UI at `http://localhost:5173` to view your browsing history
3. Use the search bar to filter URLs
4. Sort by visit count or URL alphabetically
5. Click on URLs to visit them directly

## Benefits of This Project

* **Efficient Memory Usage**: 
  - Trie structure minimizes redundancy by sharing common URL prefixes
  - Optimized data storage and retrieval

* **Quick Retrieval**: 
  - URLs can be accessed rapidly through the Trie
  - Frontend caching for improved performance
  - Real-time updates without page reload

* **Modern UI/UX**:
  - Clean, intuitive interface
  - Responsive design for all screen sizes
  - Interactive search and sorting
  - Visual indicators for visit frequency

* **Integrated Tracking**: 
  - Tracks visit counts directly
  - Visual representation of browsing patterns
  - Easy access to frequently visited sites

## Technical Architecture

### Frontend
- Built with React and Vite
- Styled with Tailwind CSS
- Real-time updates using fetch API
- Responsive and mobile-friendly design

### Backend
- Flask server with CORS support
- RESTful API endpoints
- File-based storage system
- Trie data structure implementation

### Data Flow
1. URL capture via Chrome extension
2. Server-side processing and storage
3. Trie-based data organization
4. Frontend retrieval and display

## Future Enhancements
- Add data visualization charts
- Implement user authentication
- Add export functionality
- Include browser sync capabilities

## Contributing
Contributions are welcome! Please feel free to submit a Pull Request.

## License
This project is licensed under the MIT License - see the LICENSE file for details.
