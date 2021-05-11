const express = require('express')
const app = express()
const port = 5000

app.use(express.static('public'))
const session = require('express-session')
const bodyParser = require('body-parser')
app.use(bodyParser.urlencoded({ extended: false }))

app.use(session({
    secret: 'whatever this is not rly important',
    cookie: { secure: false, maxAge: 60000 }
}))

const rand_num = () => {
    return parseInt(Math.random().toString()
        .substr(2)
        .padEnd(13, '0'))
}

const rand_nums = () => {
    nums = []
    for (i = 0; i < 10; ++i) {
        num = rand_num()
        console.log(num)
        for (j = 0; j < 18; ++j) {
            nums.push(num % 10)
            num = Math.floor(num / 10)
        }
    }
    console.log(nums)
    return nums
}

const reseed = () => {
    for (i = 0; i < 400; ++i) rand_num()
}

app.post('/submit', (req, res) => {
    if (req.session.nums) {
        req.session.attempts++

        if (req.session.attempts > 120) {
            reseed()
            req.session.nums = rand_nums()
            req.session.attempts = 1
        }
    }
    else {
        req.session.attempts = 1
        req.session.nums = rand_nums()
    }

    guess = parseInt(req.body.guess)
    correct = req.session.nums[req.session.attempts - 1]
    if (guess === correct) {
        if (req.session.score) {
            req.session.score++
        }
        else {
            req.session.score = 1
        }
        if (req.session.score == 10)
            res.json({ correct: true, flag: process.env.FLAG, score: req.session.score })
        else
            res.json({ correct: true, score: req.session.score })
    }
    else {
        req.session.score = 0
        res.json({ correct: false, answer: correct, score: req.session.score })
    }
})

app.listen(port, () => {
    console.log(`Example app listening at http://localhost:${port}`)
})