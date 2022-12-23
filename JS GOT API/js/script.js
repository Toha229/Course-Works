let pictures = [
    'https://p4.wallpaperbetter.com/wallpaper/413/495/729/game-of-thrones-wallpaper-preview.jpg'
]
const bg = document.querySelector(".background");
const h = document.getElementById("houses");
const c = document.getElementById("characters");
const hd = document.getElementById("hd");
const cd = document.getElementById("cd");

bg.setAttribute("style", 'background-image: url("' + pictures[getRandomInt(pictures.length)] +'");');

hd.addEventListener("mouseenter", Houses);
cd.addEventListener("mouseenter", Characters);
hd.addEventListener("click", clickHouses);
cd.addEventListener("click", clickCharacters);

function Houses(){
    h.setAttribute("style", "font-size: 60px;");
    c.setAttribute("style", "font-size: 50px;");
}
function Characters(){
    c.setAttribute("style", "font-size: 60px;");
    h.setAttribute("style", "font-size: 50px;");
}

function clickHouses(){
    location.href="houses.html";
}
function clickCharacters(){
    location.href="characters.html";
}

function getRandomInt(max) {
    return Math.floor(Math.random() * max);
}

