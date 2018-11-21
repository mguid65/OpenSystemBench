#include <string>
#include <curl/curl.h>

size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp)
{
   return size * nmemb;
}

class submit {
public:
  submit() {}
  long do_submission(std::string username, std::string password, std::string json_str) {
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
      curl_easy_setopt(curl, CURLOPT_URL, "https://opensystembench.com/results/submit");
      //curl_easy_setopt(curl, CURLOPT_URL, "ssh.opensystembench.com:443/results/submit");
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
#ifdef SKIP_PEER_VERIFICATION
    /*
     * If you want to connect to a site who isn't using a certificate that is
     * signed by one of the certs in the CA bundle you have, you can skip the
     * verification of the server's certificate. This makes the connection
     * A LOT LESS SECURE.
     *
     * If you have a CA cert for the server stored someplace else than in the
     * default bundle, then the CURLOPT_CAPATH option might come handy for
     * you.
     */
      curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
#endif

#ifdef SKIP_HOSTNAME_VERIFICATION
    /*
     * If the site you're connecting to uses a different host name that what
     * they have mentioned in their server certificate's commonName (or
     * subjectAltName) fields, libcurl will refuse to connect. You can skip
     * this check, but this will make the connection less secure.
     */
      curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
#endif
      curl_easy_setopt(curl, CURLOPT_USERNAME, username.c_str());
      curl_easy_setopt(curl, CURLOPT_PASSWORD, password.c_str());
      curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_str.c_str());
      curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, -1L);
    //curl_easy_setopt(curl, CURLOPT_AB);
    /* Perform the request, res will get the return code */
      res = curl_easy_perform(curl);

      /* Check for errors */
      if(res != CURLE_OK) {
        error = "HTTPS Post Request failed";
      } else {
        long response_code;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
        if(response_code == 200) {
          response = "200 OK";
        } else {
          switch(response_code) {
            case 400:
              response = "400 Bad request";
              break;
            case 401:
              response = "401 Unauthorized";
              break;
            case 403:
              response = "403 Forbidden";
              break;
            case 404:
              response = "404 Not found";
              break;
            case 418:
              response = "418 Im a teapot";
              break;
            case 500:
              response = "500 Internal server error";
              break;
            case 512:
              response = "521 Web server is down";
              break;
            default:
              response = "An unknown error occured";
              break;
          }
        }
      }
    }
  }

  void cleanup() {
    curl_easy_cleanup(curl);
    curl_global_cleanup();
  }

  std::string getError() { return error; }
  std::string getResponse() { return response; }
private:
  CURL *curl;
  std::string error = "";
  std::string response = "";
};

