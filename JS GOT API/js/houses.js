const URL = "https://api.gameofthronesquotes.xyz/v1/houses";
const houseList = document.getElementById("accordionHouses");
const sb = document.getElementById('searchBox');

let houseCount = 1;

fetch(URL).then((response) => {
    return response.json()
}).then(data => {
    data.forEach(house => {
        addHouse(house);
    });;
    localStorage.setItem('houses', JSON.stringify(data));
})
// let characters = JSON.parse(localStorage.getItem('characters'));



sb.addEventListener('input', search);

function search(e){
    findHouse(e.target.value);
}

function findHouse(name){
    let houses = JSON.parse(localStorage.getItem('houses'));
    houseList.innerHTML = "";
    houses.forEach(house =>{
        if(house.name.toLowerCase().includes(name.toLowerCase())){
            addHouse(house);
        }
    });
}


function addHouse(house) {
    let accItem = document.createElement('div');
    accItem.innerHTML=
`<div class="accordion-item">
    <h2 class="accordion-header" id="headingOne">
        <button class="accordion-button collapsed" type="button" data-bs-toggle="collapse"
            data-bs-target="#c${houseCount}" aria-expanded="false" aria-controls="c${houseCount}">
            ${house.name}
        </button>
    </h2>
    <div id="c${houseCount}" class="accordion-collapse collapse" aria-labelledby="headingOne"
        data-bs-parent="#accordionHouses">
        <div class="accordion-body">
        ${getAccBody(house.members)}
        </div>
    </div>
</div>`
    houseList.appendChild(accItem);
    houseCount++;
}

function getAccBody(characters){
    let chStr = "";
    characters.forEach(character => {
        chStr += '<p>' + character.name + '</p>\n';
    });
    return chStr;
}