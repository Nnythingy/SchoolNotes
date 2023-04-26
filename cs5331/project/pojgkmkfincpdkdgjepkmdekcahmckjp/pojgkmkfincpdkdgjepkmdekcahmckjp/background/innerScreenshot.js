let idsub, SCREENSHOTS = [],
    ID = 100,
    targetId = null,
    currentUrl = "";

function sleep(e) {
    return new Promise((t => setTimeout(t, e)))
}
chrome.runtime.onMessage.addListener((async function(e, t, r) {
    const {
        captureScreen: s,
        takeScreenshot: o,
        lastFrameHeight: a,
        lastFrame: n,
        offsetHeight: i,
        bottomOffset: l,
        offsetWidth: c,
        platform: f,
        websiteUrl: m
    } = e;
    if (s) {
        let e = {
            url: await (async () => new Promise(((e, t) => {
                chrome.tabs.captureVisibleTab(null, {
                    format: "png"
                }, (t => {
                    e(t)
                }))
            })))(),
            lastFrame: n,
            lastFrameHeight: a,
            offsetHeight: i,
            bottomOffset: l,
            offsetWidth: c,
            platform: f
        };
        SCREENSHOTS.push(e), chrome.tabs.sendMessage(t.tab.id, {
            capture: !0
        })
    }
    if (o) {
        const e = chrome.extension.getURL("options.html?id=" + ID++ + `&url=${m}&type=full_page`);
        idsub = ID - 1, currentUrl = "/options.html?id=" + idsub, chrome.tabs.onUpdated.addListener((function e(t, r) {
            if (t != targetId || "complete" != r.status) return;
            chrome.tabs.onUpdated.removeListener(e);
            const s = chrome.extension.getViews();
            for (let e = 0; e < s.length; e++) {
                let t = s[e];
                if (t.location.href.includes(currentUrl)) {
                    t.hello(SCREENSHOTS, m), SCREENSHOTS = [];
                    break
                }
            }
        })), chrome.tabs.create({
            url: e
        }, (e => {
            targetId = e.id
        }))
    }
}));