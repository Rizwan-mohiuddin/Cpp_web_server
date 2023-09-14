#include <iostream>
#include <sstream>
#include <string>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

const int PORT = 8080;

std::string generateHTMLResponse() {
    std::string html = "<html>";
    html += "<head>";
    html += "<title>Simple C++ Web Server</title>";
    html += "<style>";
    html += "body {";
    html += "    font-family: Arial, sans-serif;";
    html += "    background-color: #f4f4f4;";
    html += "    margin: 0;";
    html += "    padding: 0;";
    html += "    color: #333;";
    html += "}";

    html += "header {";
    html += "    background-color: #333;";
    html += "    color: #fff;";
    html += "    text-align: center;";
    html += "    padding: 20px;";
    html += "}";

    html += "h1 {";
    html += "    font-size: 36px;";
    html += "}";

    html += "p {";
    html += "    font-size: 18px;";
    html += "    line-height: 1.6;";
    html += "    margin: 20px;";
    html += "}";

    html += "form {";
    html += "    background-color: #fff;";
    html += "    padding: 20px;";
    html += "    border: 1px solid #ccc;";
    html += "    margin-bottom: 20px;";
    html += "    border-radius: 5px;";
    html += "}";

    html += "label {";
    html += "    display: block;";
    html += "    font-weight: bold;";
    html += "}";

    html += "input[type=\"text\"], input[type=\"password\"] {";
    html += "    width: 100%;";
    html += "    padding: 10px;";
    html += "    margin-bottom: 10px;";
    html += "    border: 1px solid #ccc;";
    html += "    border-radius: 3px;";
    html += "}";

    html += "input[type=\"submit\"] {";
    html += "    background-color: #333;";
    html += "    color: #fff;";
    html += "    padding: 10px 20px;";
    html += "    border: none;";
    html += "    cursor: pointer;";
    html += "    border-radius: 3px;";
    html += "}";

    html += "</style>";
    html += "</head>";
    html += "<body>";
    html += "<header>";
    html += "<h1>Welcome to my C++ Web Server</h1>";
    html += "</header>";
    html += "<div>";
    html += "<p>This is a simple example of a C++ Bank Management System website.</p>";

    // Banking operations forms
    html += "<h2>Banking</h2>";

    // Form for opening a new account
    html += "<form action=\"/openAcc\" method=\"post\">";
    html += "<h3>Open a New Account</h3>";
    html += "<label for=\"name\">Name:</label>";
    html += "<input type=\"text\" name=\"name\"><br>";
    html += "<label for=\"phone\">Phone:</label>";
    html += "<input type=\"text\" name=\"phone\"><br>";
    html += "<input type=\"submit\" value=\"Open Account\">";
    html += "</form>";

    // Form for viewing account details
    html += "<form action=\"/accDet\" method=\"post\">";
    html += "<h3>View Account Details</h3>";
    html += "<label for=\"accountNumber\">Account Number:</label>";
    html += "<input type=\"text\" name=\"accountNumber\"><br>";
    html += "<label for=\"pin\">Security Pin:</label>";
    html += "<input type=\"password\" name=\"pin\"><br>";
    html += "<input type=\"submit\" value=\"View Details\">";
    html += "</form>";

    // Form for depositing money
    html += "<form action=\"/deposit\" method=\"post\">";
    html += "<h3>Deposit Money</h3>";
    html += "<label for=\"accountNumber\">Account Number:</label>";
    html += "<input type=\"text\" name=\"accountNumber\"><br>";
    html += "<label for=\"pin\">Security Pin:</label>";
    html += "<input type=\"password\" name=\"pin\"><br>";
    html += "<label for=\"depositAmount\">Amount to Deposit:</label>";
    html += "<input type=\"text\" name=\"depositAmount\"><br>";
    html += "<input type=\"submit\" value=\"Deposit\">";
    html += "</form>";

    // Form for withdrawing money
    html += "<form action=\"/withdraw\" method=\"post\">";
    html += "<h3>Withdraw Money</h3>";
    html += "<label for=\"accountNumber\">Account Number:</label>";
    html += "<input type=\"text\" name=\"accountNumber\"><br>";
    html += "<label for=\"pin\">Security Pin:</label>";
    html += "<input type=\"password\" name=\"pin\"><br>";
    html += "<label for=\"withdrawAmount\">Amount to Withdraw:</label>";
    html += "<input type=\"text\" name=\"withdrawAmount\"><br>";
    html += "<input type=\"submit\" value=\"Withdraw\">";
    html += "</form>";

    html += "</div>";
    html += "</body>";
    html += "</html>";
    return html;
}



// Declare your global variables for bank management system here
static std::string pin1, pin2;
static std::string name;
static std::string phone;

// Function to generate HTML response for banking operations
std::string generateBankHTMLResponse() {
    // Implement HTML response for your bank management system here
    std::string html = "<html>";
    // Add your HTML content here
    html += "</html>";
    return html;
}

// Define functions for your banking operations here

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Error: Unable to initialize Winsock." << std::endl;
        return 1;
    }

    SOCKET serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    int clientAddrLen = sizeof(clientAddr);

    // Create a socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Error: Unable to create server socket." << std::endl;
        WSACleanup();
        return 1;
    }

    // Bind the socket to the specified port
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Error: Binding failed." << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // Start listening for incoming connections
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Error: Listening failed." << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Server is listening on port " << PORT << "..." << std::endl;

    while (1) {
        // Accept a connection from a client
        clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Error: Unable to accept client connection." << std::endl;
            continue;
        }

        // Handle the request
        char buffer[1024];
        memset(buffer, 0, sizeof(buffer));
        if (recv(clientSocket, buffer, sizeof(buffer), 0) == SOCKET_ERROR) {
            std::cerr << "Error: Unable to receive data from client." << std::endl;
            closesocket(clientSocket);
            continue;
        }

        // Parse the HTTP request to determine the requested URL
        std::string request(buffer);
        size_t pos = request.find("GET");
        if (pos != std::string::npos) {
            size_t endPos = request.find("HTTP/1.1", pos);
            if (endPos != std::string::npos) {
                std::string requestedURL = request.substr(pos + 4, endPos - pos - 5);

                // Implement logic to handle different URLs
                if (requestedURL == "/openAcc") {
                    // Handle the request for opening a new account
                    // You can call your bank management functions here
                    // Send an HTML response generated by generateBankHTMLResponse()
                    std::string response = "HTTP/1.1 200 OK\r\n";
                    response += "Content-Type: text/html\r\n";
                    response += "Connection: close\r\n\r\n";
                    response += generateBankHTMLResponse();
                    send(clientSocket, response.c_str(), response.length(), 0);
                } else {
                    // Generate and send the default HTML response
                    std::string response = "HTTP/1.1 200 OK\r\n";
                    response += "Content-Type: text/html\r\n";
                    response += "Connection: close\r\n\r\n";
                    // Use generateHTMLResponse or any other HTML response generation function
                    response += generateHTMLResponse();
                    send(clientSocket, response.c_str(), response.length(), 0);
                }
            }
        }

        closesocket(clientSocket);
    }

    closesocket(serverSocket);
    WSACleanup();
    return 0;
}

