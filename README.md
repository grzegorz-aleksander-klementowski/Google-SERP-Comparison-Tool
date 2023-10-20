# aspekt-inzynierski-do-pracy-magisterskiej
<h1>CLI SEP tool for calculating and comparing HTML elements from SERP Google results. Search and analyse thousand SERP results in few steps.</h1>

## Overview

Engineering aspect for master's thesis for Copernicus Academic Institution of Wrocław. Compares the HTML elements of web pages retrieved from the Google search results page and compares them to each ot her. It calculate most important SEO elemnts from SERP lists.

A program that analyzes Google search results to compare HTML elements on web pages.


The Engineering Aspect for Master's Thesis program is a powerful tool for analyzing Google Search Engine Results Pages (SERP). It is designed to help users gain insights into the structure and content of web pages that appear in search results.

For now is partly translated to English as the aim of the project was to use it as research tool for research paper at Polish Academic Institution.

## How to Use

The program provides two primary modes of operation:

1. **Batch Analysis**: Users have the option to provide a list of search phrases stored in a text file "default.txt". When this option is chosen, the program automatically retrieves search phrases from the file and analyzes the SERP results for each phrase on the list. This mode is particularly useful for analyzing multiple search queries in one go.

2. **Add your own elements to analysis**: Users have the option to customize and add their own elements for analysis. Simply append new search phrases to the "elementy_do_wyszukania.txt" file, starting from the second line. The program will automatically include these additional elements in the analysis.

3. **Single Query Analysis**: Alternatively, users can manually enter a single search phrase directly into the terminal. In this mode, the program will perform an analysis of the SERP results specific to the entered query. This mode is suitable for quick, one-off analyses.

4.  **Saved results**: Results from SERP analysis are in 'searched_google_sites/przeanalizowane_wyniki_serp.txt'. Results from analysys of particular websites are in 'ostatnie_analizy_stron/'.

## Key Features

- Counting and comparing HTML elements within SERP results.
- Tracking the frequency of specific keywords in SERP results.
- Displaying the placement of web pages in the SERP.
- Evaluating the importance of HTML tags and keyword usage.

## Example Use Case

For instance, if you enter the search query "house in Wrocław," the program will count how many times the words "house" and "Wrocław" appear on web pages within the SERP. It will also determine the placement of each web page in the SERP rankings. Furthermore, the program will analyze the frequency of HTML tags used in the SERP, providing insights into which tags are most commonly employed and how frequently specific keywords should be used within those tags.

The Engineering Aspect for Master's Thesis program empowers users to make informed decisions regarding HTML structure and keyword usage based on real-world SERP data, enhancing the effectiveness of web content optimization strategies.

## Requirements

- Linux Operating System
- C++ Compiler (e.g., g++)
- Code::Blocks IDE (optional for development)

## Sample Results

You can include sample analysis results here if applicable.

## Author

- Grzegorz Aleksander Klementowski
- grzegorz.aleksander@klementowski.pl
- grzegorz-aleksander.klementowski.pl

## Contact

If you have any questions or suggestions, feel free to contact me at grzegorz.aleksander@klementowski.pl.

## License

This project is open-source and freely available for use. Attribution to the author is appreciated but not required.
