# Efficient Browser History Tracker

This project is an efficient browser history tracker built using a custom Chrome extension, a Python server, and a Trie-based C++ program. The purpose is to capture, store, and retrieve browser history with optimized memory usage and quick access.

## Project Overview

This setup overcomes the limitations of traditional browser history storage by reducing redundancy and improving retrieval speed. It’s especially useful for tracking frequently accessed sites or performing customized analysis on browsing data.

## How It Works

1. **Chrome Extension**: Captures each visited URL and sends it to a local Python server in real-time.
2. **Python Server**: Receives URLs from the Chrome extension and appends them to `urls.txt`, creating a central log of visited sites.
3. **C++ Program**: Reads URLs from `urls.txt`, stores each URL in a Trie data structure for efficient tracking, and displays visit counts.

## Getting Started

1. **Set up the Python server** to start receiving URLs.
2. **Load the Chrome extension** in developer mode to begin capturing URLs as you browse.
3. **Run the C++ program** to monitor and display the URL history, along with visit counts.

## Benefits of This Project

- **Efficient Memory Usage**: The Trie structure minimizes redundancy by sharing common URL prefixes.
- **Quick Retrieval**: URLs can be accessed rapidly through the Trie, regardless of the history size.
- **Integrated Tracking**: Tracks visit counts directly, without the need for additional data structures.

This project provides a lightweight, scalable history-tracking solution that improves on traditional methods by offering faster access and custom tracking capabilities.
