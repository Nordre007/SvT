#include <stdio.h>
#include <curl/curl.h>

struct MemoryChunk {
    char* memory;
    size_t size;
};

size_t write_callback(void* incoming, size_t size, size_t nmemb, void* userdata) {
    size_t size_total = size * nmemb;
    struct MemoryChunk* buf = (struct MemoryChunk*) userdata; 
}

int main() {

    CURL* handler = curl_easy_init(); 

    CURLcode result = curl_global_init(CURL_GLOBAL_ALL);


    if(handler) {
        curl_easy_setopt(handler, CURLOPT_URL, "http://api.texttv.nu/api/get/100?includePlainTextContent=1");
        curl_easy_setopt(handler, CURLOPT_WRITEFUNCTION, write_callback);

        result = curl_easy_perform(handler);

        if(result != CURLE_OK) 
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
            
    }
    return 0;
}