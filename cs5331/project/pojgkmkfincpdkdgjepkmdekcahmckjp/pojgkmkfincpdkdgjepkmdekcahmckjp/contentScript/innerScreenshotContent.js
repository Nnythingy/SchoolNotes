console.log("Inner script loaded");
var webpageHeight = $(document).height(),
    getBodyBackground = () => window.getComputedStyle(document.body).getPropertyValue("background-color"),
    ytApp = document.getElementsByTagName("ytd-app") && document.getElementsByTagName("ytd-app")[0];

function getHeightestElement() {
    const e = function(e) {
        let t = window.getComputedStyle(e)["overflow-y"];
        return ("scroll" === t || "auto" === t) && e.scrollHeight > e.clientHeight && 0 !== e.clientHeight
    };
    let t = document.body.getElementsByTagName("*"),
        i = document.getElementsByTagName("body")[0],
        n = document.body.scrollHeight > window.innerHeight ? i : null;
    for (let i = 0; i < t.length; i++) {
        let o = t[i];
        if (o.scrollHeight >= o.clientHeight && e(o) && o.scrollHeight - o.clientHeight > 50) {
            if (!n) {
                n = o;
                continue
            }
            o.scrollHeight >= n.scrollHeight && (n = o)
        }
    }
    return n || i
}
var getFixedStickyElements = () => $("*").filter((function() {
        return $(this).css("position").toLowerCase().indexOf("fixed") > -1
    })),
    getStickyElements = () => $("*").filter((function() {
        return $(this).css("position").toLowerCase().indexOf("sticky") > -1
    })),
    getStickyAndFixedElements = () => $("*").filter((function() {
        return $(this).css("position").toLowerCase().indexOf("fixed") > -1 || $(this).css("position").toLowerCase().indexOf("sticky") > -1
    })),
    isInViewport = e => {
        const t = e.getBoundingClientRect();
        return t.y > 0 && t.y < window.innerHeight && t.y < e.clientHeight || t.top >= 0 && t.left >= 0 && t.bottom <= (window.innerHeight || document.documentElement.clientHeight) && t.right <= (window.innerWidth || document.documentElement.clientWidth)
    };

function sleep(e) {
    return new Promise((t => setTimeout(t, e)))
}
var scrollView = async e => new Promise(((e, t) => {
    window.innerHeight, window.scrollBy(0, 100), e()
})), capture = async (e = !1, t = 0, i = 948, n = 0, o = 1905, s) => new Promise(((l, c) => {
    chrome.runtime.sendMessage({
        captureScreen: !0,
        lastFrame: e,
        bottomOffset: n,
        lastFrameHeight: t,
        offsetHeight: i,
        offsetWidth: o,
        platform: s
    }, (function(e) {
        chrome.runtime.onMessage.addListener((async function(e, t, i) {
            e.capture && l()
        }))
    }))
})), checkedElements = [], checkForFixedElements = async () => new Promise(((e, t) => {
    let i = getFixedStickyElements() || [];
    for (let e = 0; e < i.length; e++) {
        let t = i[e];
        if (t == document.body) continue;
        let n = t.getAttribute("class") && t.getAttribute("class").split(" ").join(".") ? "." + t.getAttribute("class").split(" ").join(".") : null,
            o = t.getAttribute("id") && t.getAttribute("id") ? "#" + t.getAttribute("id") : null;
        checkedElements.includes(t) || isInViewport(t) && (o ? o = o.split("#")[1] : n && (n = n.split(".")[1]))
    }
    e()
})), hideFixed = async () => new Promise(((e, t) => {
    let i = getFixedStickyElements() || [];
    for (let e = 0; e < i.length; e++) {
        let t = i[e];
        t != document.body && (t.getAttribute("class") && t.getAttribute("class").split(" ").join(".") && t.getAttribute("class").split(" ").join("."), t.getAttribute("id") && t.getAttribute("id") && t.getAttribute("id"), checkedElements.includes(t) || isInViewport(t) && (t.style.visibility = "hidden", checkedElements.push(t)))
    }
    e()
})), checkForStickyElems = () => new Promise(((e, t) => {
    let i = getStickyElements() || [];
    for (let t = 0; t < i.length; t++) {
        let n = i[t],
            o = n.getAttribute("class") && n.getAttribute("class").split(" ").join(".") ? "." + n.getAttribute("class").split(" ").join(".") : null,
            s = n.getAttribute("id") && n.getAttribute("id") ? "#" + n.getAttribute("id") : null;
        checkedElements.includes(n) && e();
        let {
            top: l
        } = n.getBoundingClientRect();
        isInViewport(n) && (s ? (document.querySelector(s).style.visibility = "hidden", checkedElements.push(n)) : o && (document.querySelector(o).style.visibility = "hidden", checkedElements.push(n)))
    }
    e()
})), removeAllExceptHeightest = async (e, t) => new Promise(((t, i) => {
    e == ytApp && ($("#guide-content").css({
        visibility: "hidden",
        opacity: 0
    }), $("#page-manager").parents().siblings().each((function() {
        $(this).css({
            visibility: "hidden",
            opacity: 0
        })
    })), t()), $(e).siblings().each((function(e) {
        $(this).css({
            visibility: "hidden",
            opacity: 0
        })
    })), $(e).parents().siblings().each((function(e) {
        $(this).css({
            visibility: "hidden",
            opacity: 0
        })
    })), t()
})), checkHeightestPlusFixed = async (e, t) => new Promise(((i, n) => {
    let o = {
        yes: !1,
        ele: null
    };
    for (let i = 0; i < e.length; i++) {
        let n = e[i];
        t == n ? o = {
            yes: !0,
            ele: t
        } : t.parentElement == n && (o = {
            yes: !0,
            ele: t.parentElement
        })
    }
    i(o)
})), recalculateFrames = async (e, t, i, n, o) => new Promise(((s, l) => {
    let c = Math.ceil(e.scrollHeight / window.innerHeight);
    if (t == c) {
        let e = Math.ceil((i - n) / o);
        0 == !e && (c = c + e - 1)
    }
    s(c)
}));
async function main(e) {
    let t, i, n, o, s, l = 0,
        c = window.innerHeight,
        r = window.innerWidth,
        d = 0,
        a = 1,
        u = !1,
        g = t == document.body,
        h = !1,
        m = document.querySelector("div[role='feed']");
    switch (m && (s = m.childElementCount / 5), e) {
        case "facebook":
            t = document.body, i = c, n = m.scrollHeight, window.scrollBy(0, -2e3);
            break;
        case "youtube":
            t = document.getElementsByTagName("ytd-app")[0], i = c, n = t.scrollHeight, t.scrollBy(0, -t.scrollTop);
            break;
        default:
            t = getHeightestElement(), i = t == document.body ? window.innerHeight : t.offsetHeight, n = t.scrollHeight, t.scrollBy(0, -t.scrollTop)
    }
    d = Math.ceil(t.scrollHeight / c), o = t.getBoundingClientRect();
    let y = Math.abs(n - d * c),
        f = c,
        b = r,
        w = c - o.bottom;
    for (document.body.style.overflowX = "hidden", t.style.overflowX = "hidden", document.body.style.overflowY = "hidden", t.style.overflowY = "hidden"; l < n;) {
        if (a >= d || l > 2e4 ? (u = !0, y = n - l) : u = !1, h) switch (e) {
            case "facebook":
                document.querySelector("div[role='banner']").style.visibility = "hidden";
                break;
            case "youtube":
                break;
            case "adobe":
                $("canvas").css({
                    visibility: "visible",
                    opacity: 1
                })
        }
        await sleep(500), await capture(u, y, f, w, b, g, e), await checkForStickyElems(), t && (t == document.body || t == ytApp ? window.scrollBy(0, i) : (t.scrollBy(0, i), 1 == a && await sleep(500)));
        let r = !0;
        switch (e) {
            case "facebook":
                await hideFixed(), a == s && (r = !1), n = m.scrollHeight, f = m.offsetHeight, b = m.offsetWidt;
                break;
            case "youtube":
                n = t.scrollHeight, f = t.offsetHeight, b = t.offsetWidth;
                break;
            default:
                await checkForFixedElements(), n = t.scrollHeight, f = t.offsetHeight, b = t.offsetWidth, w = c - o.bottom
        }
        if (!r) break;
        if (a++, l += i, l > 2e4) break;
        if (1 == b) break;
        h = !0, d = await recalculateFrames(t, a, n, l, f), await removeAllExceptHeightest(t, o)
    }
    chrome.runtime.sendMessage({
        takeScreenshot: !0,
        websiteUrl: window.location.href
    }), window.location.reload()
}
chrome.runtime.onMessage.addListener((async function(e, t, i) {
    if ("start" == e.message) {
        let t = null,
            {
                url: i
            } = e;
        i.includes("facebook.com") ? t = "facebook" : i.includes("youtube.com") && (t = "youtube"), await main(t)
    } else e.message
}));