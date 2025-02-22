#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define API_KEY "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"  
#define API_URL "https://api.openai.com/v1/chat/completions"
#define MAX_INPUT_SIZE 1024
#define MAX_RESPONSE_SIZE 10000

// Structure to store response data
struct ResponseData {
    char *data;
    size_t size;
};

// Callback function to handle API response
size_t write_callback(void *ptr, size_t size, size_t nmemb, void *userdata) {
    struct ResponseData *response = (struct ResponseData *)userdata;
    size_t total_size = size * nmemb;

    // Reallocate memory to store response
    response->data = realloc(response->data, response->size + total_size + 1);
    if (response->data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 0;
    }

    // Append new data and null-terminate
    memcpy(response->data + response->size, ptr, total_size);
    response->size += total_size;
    response->data[response->size] = '\0';

    return total_size;
}

int main() {
    CURL *curl;
    CURLcode res;
    char user_input[MAX_INPUT_SIZE];

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if (!curl) {
        fprintf(stderr, "Failed to initialize CURL\n");
        return 1;
    }

    while (1) {
        printf("\nYou: ");
        fgets(user_input, MAX_INPUT_SIZE, stdin);
        user_input[strcspn(user_input, "\n")] = 0;  // Remove newline

        // Exit chat if user types "exit"
        if (strcmp(user_input, "exit") == 0) {
            printf("Exiting chat...\n");
            break;
        }

        // Prepare JSON payload
        char json_payload[MAX_INPUT_SIZE + 512];
        snprintf(json_payload, sizeof(json_payload),
            "{"
            "\"model\": \"gpt-4\","
            "\"messages\": [{\"role\": \"user\", \"content\": \"%s\"}],"
            "\"temperature\": 0.7"
            "}", user_input);

        // Setup headers
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");

        char auth_header[256];
        snprintf(auth_header, sizeof(auth_header), "Authorization: Bearer %s", API_KEY);
        headers = curl_slist_append(headers, auth_header);

        // Response data structure
        struct ResponseData response = {NULL, 0};

        // Set up CURL options
        curl_easy_setopt(curl, CURLOPT_URL, API_URL);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_payload);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // Perform the request
        res = curl_easy_perform(curl);

        if (res == CURLE_OK) {
            printf("\nChatGPT: %s\n", response.data);
        } else {
            fprintf(stderr, "CURL request failed: %s\n", curl_easy_strerror(res));
        }

        // Cleanup response data
        free(response.data);
        curl_slist_free_all(headers);
    }

    curl_easy_cleanup(curl);
    curl_global_cleanup();
    return 0;
}
