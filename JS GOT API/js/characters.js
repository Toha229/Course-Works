const URL = "https://thronesapi.com/api/v2/Characters";
const charactersTable = document.querySelector(".characters-table");
const charactersList = document.querySelector(".characters-list");
const sb = document.getElementById('searchBox');
const loadMore = document.getElementById('loadMore');
let searchCharacter = "";
let blockView = false;

fetch(URL).then(response => {
    return response.json()
}).then(data => {
    localStorage.setItem('characters', JSON.stringify(data));
})

sb.addEventListener('input', search);

showCharacters(0, 20);

function search(e) {
    charactersTable.innerHTML = "";
    searchCharacter = e.target.value;
    showCharacters(0, 20);
}

loadMore.setAttribute("onclick", "showCharacters(charactersTable.children.length, 20);");

function showCharacters(offset, count) {
    let characters = JSON.parse(localStorage.getItem('characters'));
    for (let i = offset; charactersTable.children.length < offset + count; i++) {
        if (i == characters.length) {
            loadMore.style.display = "none";
            return;
        }
        if (characters[i].fullName.toLowerCase().includes(searchCharacter.toLowerCase())) {
            createCharacterPrevTable(characters[i]);
        }
    }
    loadMore.style.display = "block";
}

function createCharacterPrev(character) {
    let prevDiv = document.createElement('div');
    prevDiv.setAttribute('class', 'character-preview');

    let infoDiv = document.createElement('div');
    infoDiv.setAttribute('class', 'character-info');

    let p = createCharacterInfo(character.fullName);
    p.setAttribute('style', 'font-weight: bold;');
    infoDiv.appendChild(p);
    infoDiv.appendChild(createCharacterInfo('Title: ' + character.title));
    infoDiv.appendChild(createCharacterInfo('Family: ' + character.family));

    let imgPortrait = document.createElement('img');
    imgPortrait.setAttribute('class', 'portrait');
    imgPortrait.setAttribute('src', character.imageUrl);

    prevDiv.appendChild(infoDiv);
    prevDiv.appendChild(imgPortrait);
    charactersList.appendChild(prevDiv);
}

function createCharacterPrevTable(character) {
    let tr = document.createElement('tr');
    tr.setAttribute("class", "table-light");
    tr.innerHTML =
        `<th scope="row" width="25%"><h3>${character.fullName}</h3></th>
<td width="25%"><h3>${character.title}</h3></td>
<td width="25%"><h3>${character.family}</h3></td>
<td width="25%"><img src="${character.imageUrl}" class="portrait"/></td>`;
    charactersTable.appendChild(tr);
}

function createCharacterInfo(text) {
    let p = document.createElement('p');
    p.setAttribute('class', 'character-info');
    p.textContent = text;
    return p;
}