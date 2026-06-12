#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>
#include "getpage.h"


struct MemoryChunk {
    char* memory;
    size_t size;
};

size_t write_callback(void* incoming, size_t size, size_t nmemb, void* userdata) {
    size_t size_total = size * nmemb;
    struct MemoryChunk* mem = (struct MemoryChunk*) userdata;
    
    char* ptr = realloc(mem->memory, mem->size + size_total + 1);

    if(!ptr) {
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), incoming, size_total);
    mem->size += size_total;
    mem->memory[mem->size] = 0;
    return size_total;
}

char* parse_response(const char* json_str) {
    cJSON* root = cJSON_Parse(json_str);
    if(!root) {
        fprintf(stderr, "JSON parse error: %s\n", cJSON_GetErrorPtr());
        return NULL;
    }

    cJSON* first = cJSON_GetArrayItem(root, 0);
    if(!first) {
        cJSON_Delete(root); 
        return NULL;
    }

    cJSON* content_plain = cJSON_GetObjectItem(first, "content_plain");
    if(cJSON_IsArray(content_plain)) {
        cJSON* text = cJSON_GetArrayItem(content_plain, 0);
        if(cJSON_IsString(text)) {
            char* returnString = malloc(strlen(text->valuestring) + 1);
            strcpy(returnString, text->valuestring);
            cJSON_Delete(root);
            return returnString;
        }
    }

    cJSON_Delete(root);
    return NULL;
}

char* get_page_by_number(int pageNumber) {

    CURLcode result = curl_global_init(CURL_GLOBAL_ALL);

    CURL* handler = curl_easy_init(); 

    char URL[100];
    snprintf(URL, sizeof(URL), "https://api.texttv.nu/api/get/%d?includePlainTextContent=1&app=LTHtexttv", pageNumber);
    struct MemoryChunk response = {0};

    char* resultString = NULL;

    if(handler) {
        curl_easy_setopt(handler, CURLOPT_URL, URL);
        curl_easy_setopt(handler, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(handler, CURLOPT_WRITEDATA, &response);
        //curl_easy_setopt(handler, CURLOPT_FOLLOWLOCATION, 1L);

        result = curl_easy_perform(handler);

        if(result != CURLE_OK){
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
        } else {
            resultString = parse_response(response.memory);
        } 
        curl_easy_cleanup(handler);
    }

    free(response.memory);
    curl_global_cleanup();
    return resultString;
}