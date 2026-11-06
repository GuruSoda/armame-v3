console.log('Armame V1')

document.DOMContentLoaded = function () {
    console.log('Ahi vamos!')
}

var botonBuscar = document.getElementById('buscar')
botonBuscar.onclick = buscar

var inputBusqueda = document.getElementById('busqueda')
inputBusqueda.onkeyup = procesarEnter

function buscar () {

    console.log('A Buscar: ' + document.getElementById('busqueda').value)

    var vectorResultado = resultadoBusqueda(document.getElementById('busqueda').value);

    var elementoResultado = document.getElementById('resultado')

    while (elementoResultado.firstChild) {
        elementoResultado.removeChild(elementoResultado.firstChild);
    }

    elementoResultado.appendChild(armarTablaGames(vectorResultado))    
}

function armarTablaGames(vectorResultadoBusqueda) {

    var listado = document.createElement('ul')

    listado.className = "collection with-header"

   listado.innerHTML = '<li class="collection-header center"><h5>' + vectorResultadoBusqueda.length + ' Juegos Encontrados</h5></li>'

    for (var i = 0;i<vectorResultadoBusqueda.length ;i++) {
        var nodo = document.createElement('li')
        nodo.className = "collection-item hoverable"
        
        nodo.innerHTML = vectorResultadoBusqueda[i].description

        listado.appendChild(nodo)
    }

    return listado;
}

function resultadoBusqueda(cadenaBusqueda) {
    var req = new XMLHttpRequest();
    req.open('GET', 'http://www.planetaguru.com.ar/armamews/search?p='+cadenaBusqueda, false); 
    req.send(null);

//    console.log('Status: ' + req.status)

    if (req.status == 200) {
        return vector = JSON.parse(req.responseText)
   } else {
        return []
    }
}

// https://www.w3schools.com/howto/howto_js_trigger_button_enter.asp
function procesarEnter(event) {

    if (event.keyCode === 13){
        event.preventDefault()

        document.getElementById('buscar').click()
    }

}