from http.server import BaseHTTPRequestHandler, HTTPServer
from http import cookies
from sys import argv
import json
import datetime

port = 8080
if len(argv) == 2:
    port = int(argv[1])

domain = "http://127.0.0.1"
f_url = f"{domain}:{port}"
path = {"/a" : "executeScript->iframe",
        "/b" : "iframe.src", 
        "/b2": "iframe.src", 
        "/b3": "openf->XMLHTTP->iframe.src", 
        "/c" : "passf->XMLHTTP->executeScript->iframe", 
        "/d" : "xmlopen->XMLHTTP",
        "/e" : "chrome.cookie.set"}

class handler(BaseHTTPRequestHandler):
    def set_my_cookies(self):
        C = cookies.SimpleCookie()
        id = self.path.strip("/")
        name = "5331_" + id
        C[name] = (id + "_cookie5331_" + path[self.path])
        C[name]["domain"] = "127.0.0.1"
        C[name]["path"] = "/"
        expires = datetime.datetime.utcnow() + datetime.timedelta(days=1)
        C[name]["expires"] = expires.strftime("%a, %d %b %Y %H:%M:%S GMT")
        
        # enables cross-site usage
        C[name]["secure"] = True
        C[name]["samesite"] = None
        return C.output(header='')
        
    def _set_headers(self):
        self.send_response(200)
        self.send_header('Content-type', 'application/json')

        if self.path in path:
            cookie = self.set_my_cookies()
            print(self.path, cookie) #
            self.send_header('Set-Cookie', cookie)
        self.end_headers()
    
    # dummy page w/ cookies for appropriate paths
    def do_GET(self):
        self._set_headers()
        response = {"test":"feed cookie"}
        self.wfile.write(json.dumps(response).encode())

    # reply with paths
    def do_POST(self):
        cont_length = int(self.headers['Content-Length'])
        post_data = self.rfile.read(cont_length)
        print(f"\nPOST request,\nPath: {str(self.path)}\
              \nHeaders:\n{self.headers}\nBody:\n{post_data.decode()}\n\n\n")
        
        self._set_headers()
        path_key = list(path.keys())
        response = {"a" :f_url+path_key[0],
                    #"b" :f_url+path_key[1], # ignored
                    "b2":f_url+path_key[2],
                    "b3":f_url+path_key[3],
                    "c" :f_url+path_key[4],
                    #"d" :f_url+path_key[5], # ignored 
                    "e" :[domain, "5331_e", "e_cookie5331_chrome.cookie.set"]
                    }
        
        self.wfile.write(json.dumps(response).encode())


def run(server_class=HTTPServer, handler_class=handler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print("Starting httpd...\n")
    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        pass
    httpd.server_close()
    print("Stopping httpd...\n")

if __name__ == '__main__':
        run(port=port)