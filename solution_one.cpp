#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <curl/curl.h>

const std::string API_KEY = "YOUR_API_KEY"; // Replace with your API key from SmartyStreets

// Struct to hold the response from the API
struct AddressResponse {
    std::string street;
    std::string city;
    std::string zipCode;
    std::string correctedAddress;
    std::string correctedCity;
    std::string correctedZipCode;
    std::string correctedZipCodePlus4;
    bool isValid;
};

// Callback function for curl write operation
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

// Function to validate an address using the SmartyStreets API
AddressResponse validateAddress(const std::string& street, const std::string& city, const std::string& zipCode) {
    AddressResponse response;
    response.street = street;
    response.city = city;
    response.zipCode = zipCode;
    response.isValid = false;

    std::string url = "https://us-street.api.smartystreets.com/street-address?auth-id=" + API_KEY +
                      "&street=" + street +
                      "&city=" + city +
                      "&zipcode=" + zipCode;

    CURL* curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

        std::string apiResponse;
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &apiResponse);

        CURLcode res = curl_easy_perform(curl);
        if (res == CURLE_OK) {
            curl_easy_cleanup(curl);

            // Parse the JSON response to check if the address is valid
            // Note: For simplicity, we are not using a full-fledged JSON parser here.
            // This implementation assumes the specific JSON format returned by the API.
            size_t start = apiResponse.find("\"delivery_line_1\":\"");
            if (start != std::string::npos) {
                size_t end = apiResponse.find("\",", start + 19);
                response.correctedAddress = apiResponse.substr(start + 19, end - start - 19);

                start = apiResponse.find("\"city_name\":\"", end + 3);
                end = apiResponse.find("\",", start + 12);
                response.correctedCity = apiResponse.substr(start + 12, end - start - 12);

                start = apiResponse.find("\"zipcode\":\"", end + 3);
                end = apiResponse.find("\"", start + 11);
                response.correctedZipCode = apiResponse.substr(start + 11, end - start - 11);

                start = apiResponse.find("\"plus4_code\":\"", end + 1);
                if (start != std::string::npos) {
                    end = apiResponse.find("\"", start + 14);
                    response.correctedZipCodePlus4 = apiResponse.substr(start + 14, end - start - 14);
                }

                response.isValid = true;
            }
        }
    }

    return response;
}

int main() {
    std::cout << "Street, City, Zip Code -> Corrected Address, Corrected City, Corrected Zip Code" << std::endl;

    std::string line;
    while (std::getline(std::cin, line)) {
        if (line == "Street, City, Zip Code") continue; // Skip the header row

        std::stringstream ss(line);
        std::string street, city, zipCode;
        std::getline(ss, street, ',');
        std::getline(ss, city, ',');
        std::getline(ss, zipCode);

        AddressResponse response = validateAddress(street, city, zipCode);

        if (response.isValid) {
            std::cout << response.street << ", " << response.city << ", " << response.zipCode
                      << " -> " << response.correctedAddress << ", " << response.correctedCity
                      << ", " << response.correctedZipCode << "-" << response.correctedZipCodePlus4 << std::endl;
        } else {
            std::cout << response.street << ", " << response.city << ", " << response.zipCode
                      << " -> Invalid Address" << std::endl;
        }
    }

    return 0;
}
