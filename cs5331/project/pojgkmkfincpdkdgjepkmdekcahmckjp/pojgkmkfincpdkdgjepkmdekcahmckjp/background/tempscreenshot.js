let canvas, img1, imgWidth, element, webUrl, urlTimeGroup, body1 = document.getElementById("target1"),
    currentvh = 0,
    imgCount = 1,
    totalWidth = 0,
    totalHeight = 0,
    leftOver = 0,
    finalurl = "",
    left = 0,
    selectedTop = 0,
    width = 0,
    height = 0,
    emojiPicker = "";
var defaultOptions = {
        format: "image/png",
        quality: .92,
        width: void 0,
        height: void 0,
        Canvas: void 0,
        crossOrigin: void 0
    },
    mergeImages = function(t, e) {
        return void 0 === t && (t = []), void 0 === e && (e = {}), new Promise((function(a) {
            var i = (e = Object.assign({}, defaultOptions, e)).Canvas ? new e.Canvas : window.document.createElement("canvas"),
                r = e.Image || window.Image,
                o = t.map((function(t) {
                    return new Promise((function(a, i) {
                        "Object" !== t.constructor.name && (t = {
                            src: t
                        });
                        var o = new r;
                        o.crossOrigin = e.crossOrigin, o.onerror = function() {
                            return i(new Error("Couldn't load image"))
                        }, o.onload = function() {
                            return a(Object.assign({}, t, {
                                img: o
                            }))
                        }, o.src = t.src
                    }))
                })),
                n = i.getContext("2d");
            a(Promise.all(o).then((function(t) {
                var a = function(a) {
                    return e[a] || Math.max.apply(Math, t.map((function(t) {
                        return t.img[a]
                    })))
                };
                i.width = a("width");
                let r = a("height") / t[0].vh;
                return t[0].lastFrameHeight ? i.height = imgCount * a("height") - (a("height") - t[0].lastFrameHeight * r) : i.height = imgCount * a("height"), totalWidth = a("width"), t.forEach((function(t, e, i) {
                    return n.globalAlpha = t.opacity ? t.opacity : 1, t.lastFrame ? n.drawImage(t.img, t.x, a("height") - t.lastFrameHeight * r, totalWidth, t.lastFrameHeight * r, 0, e * a("height"), totalWidth, t.lastFrameHeight * r) : n.drawImage(t.img, t.x || 0, e * a("height") || 0)
                })), e.Canvas && "image/jpeg" === e.format ? new Promise((function(t, a) {
                    i.toDataURL(e.format, {
                        quality: e.quality,
                        progressive: !1
                    }, (function(e, i) {
                        e ? a(e) : t(i)
                    }))
                })) : i.toDataURL(e.format, e.quality)
            })))
        }))
    };

function setScreenshotUrl(t, e, a, i, r, o = "none") {
    imgCount = t.length;
    let n, l = [];
    leftOver = 0, t.forEach(((e, o) => {
        n = {
            src: e,
            x: 0,
            y: currentvh,
            leftOver: i,
            lastFrame: !1,
            lastFrameHeight: r,
            vh: a
        }, o === t.length - 1 && 0 != o && (n.lastFrame = !0), l.push(n), currentvh += a
    })), mergeImages(l).then((t => {
        finalurl = t, body1.src = t, body1.style.width = "90%", i && (body1.style.width = `${i}px`, body1.style.height = `${a}px`), webUrl = e, chrome.storage.local.set({
            webUrl: e
        })
    }))
}
async function hello(t, e) {
    if (!t || t.length <= 0) return;
    webUrl = e;
    let a = await InnerScrollMerge(t);
    body1.src = a, body1.style.width = "90%"
}
const InnerScrollMerge = async t => new Promise((async (e, a) => {
    let i, r = new Image;
    r.src = t[0].url, await r.decode();
    var o = document.createElement("canvas");
    o.setAttribute("id", "c");
    const n = o.getContext("2d");
    t[0];
    let l = window.innerHeight,
        g = r.naturalWidth;
    o.width = g, o.height = l * t.length;
    let h = r.naturalHeight / t[0].offsetHeight,
        s = 0,
        m = 0,
        f = 0;
    for (let e = 0; e < t.length; e++) {
        let a = t[e];
        const i = new Image;
        i.crossOrigin = "", i.src = a.url, await i.decode(), a.lastFrame ? f += a.lastFrameHeight : a.offsetHeight < l ? f += a.offsetHeight : (f += i.naturalHeight, i.naturalHeight > m && (m = i.naturalHeight))
    }
    o.height = f * h;
    for (let e = 0; e < t.length; e++) {
        let a = t[e];
        const r = new Image;
        if (r.crossOrigin = "", r.src = a.url, await r.decode(), -1 === Math.sign(a.bottomOffset) && (a.bottomOffset = 0), a.offsetHeight && a.offsetHeight <= t[0].offsetHeight) {
            if (a.lastFrame && e + 1 == t.length) {
                n.drawImage(r, 0, r.naturalHeight - (a.lastFrameHeight + a.bottomOffset) * h, g, a.lastFrameHeight * h, 0, s, g, a.lastFrameHeight * h), i = o.toDataURL();
                continue
            }
            n.drawImage(r, 0, r.naturalHeight - (a.offsetHeight + a.bottomOffset) * h, g, a.offsetHeight * h, 0, s, g, a.offsetHeight * h), s += a.offsetHeight * h, i = o.toDataURL()
        } else {
            if (a.platform && "facebook" == a.platform && a.lastFrame) break;
            a.lastFrame && e + 1 == t.length ? (n.drawImage(r, 0, r.naturalHeight - (a.lastFrameHeight + a.bottomOffset) * h, g, a.lastFrameHeight * h, 0, s, g, a.lastFrameHeight * h), i = o.toDataURL()) : (n.drawImage(r, 0, 0 - a.bottomOffset * h, g, r.naturalHeight - a.bottomOffset * h, 0, s, g, r.naturalHeight - a.bottomOffset * h), s = s + r.naturalHeight - a.bottomOffset * h, i = o.toDataURL())
        }
    }
    e(i)
}));