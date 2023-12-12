#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>


// Define your Google Maps API key
#define API_KEY "YOUR_GOOGLE_MAPS_API_KEY"

// Google Maps Geocoding API endpoint
#define GEOCODING_ENDPOINT "https://maps.googleapis.com/maps/api/geocode/json"

// A simple structure to store the response data
struct MemoryStruct {
  char *memory;
  size_t size;
};

// Callback function to handle the response data
static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;

  mem->memory = realloc(mem->memory, mem->size + realsize + 1);
  if (mem->memory == NULL) {
    // Out of memory
    fprintf(stderr, "Not enough memory (realloc returned NULL)\n");
    return 0;
  }

  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;

  return realsize;
}

// Function to perform a geocoding request
void performGeocodingRequest(const char *address) {
  CURL *curl;
  CURLcode res;

  // Initialize libcurl
  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl = curl_easy_init();
  if (curl) {
    // Set the URL
    char url[256];
    snprintf(url, sizeof(url), "%s?address=%s&key=%s", GEOCODING_ENDPOINT, address, API_KEY);
    curl_easy_setopt(curl, CURLOPT_URL, url);

    // Set the callback function to handle the response
    struct MemoryStruct chunk;
    chunk.memory = malloc(1);
    chunk.size = 0;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

    // Perform the request
    res = curl_easy_perform(curl);

    // Check for errors
    if (res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    else
      printf("Response:\n%s\n", chunk.memory);

    // Clean up
    free(chunk.memory);
    curl_easy_cleanup(curl);
  }

  // Clean up libcurl
  curl_global_cleanup();
}

int main() {
  const char *location = "1600 Amphitheatre Parkway, Mountain View, CA";
  performGeocodingRequest(location);

  return 0;
}
