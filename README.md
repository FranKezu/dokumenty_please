# 🎮 *Dokumenty Please*

### 🧑‍🤝‍🧑 **Integrantes**  
Ariel Leiva, Franco Bernal, Hugo Palomino, Felipe Romero  

### 🧾 **Asignatura**  
Estructura de Datos (ICI2240-2)  

### 📅 **Fecha de entrega**  
27-06-2025  

<div align="center">

<img src="assets/portada.jpg" width="450px" alt="Portada del proyecto"/>

---

### 📸 **Presentación del equipo**

<table>
  <tr>
    <td align="center">
      <img src="https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcRNeB-7epLFmbS-qUpHaZ5PONeak5rjSbvFz-csl5f3UTz1X8p091xm5UlOPGdszO1y4Nw&usqp=CAU" width="140px" alt="Franco Bernal"/><br/>
      <strong>Franco Bernal</strong>
    </td>
    <td align="center">
      <img src="https://thumbs.dreamstime.com/b/canina-nerviosa-prepar%C3%A1ndose-para-una-importante-entrevista-de-trabajo-vestida-con-un-traje-peque%C3%B1o-y-sentada-en-escritorio-366742856.jpg" width="140px" alt="Ariel Leiva"/><br/>
      <strong>Ariel Leiva</strong>
    </td>
    <td align="center">
      <img src="https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcT5nGHdJsfETtE8GiME7ddb2bpk1HzJPi28hw&s" width="140px" alt="Felipe Romero"/><br/>
      <strong>Felipe Romero</strong>
    </td>
    <td align="center">
      <img src="https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcTNP7paUaZNRj8LnZL_xta03_lQTGtnfOIxvRMFliCCpbw7iwHk0oIdMSmZCXtH_XQqeMM&usqp=CAU" width="140px" alt="Hugo Palomino"/><br/>
      <strong>Hugo Palomino</strong>
    </td>
  </tr>
</table>

</div>

---


## 🚀 ¿Cómo ejecutar el juego?

### 🟢 Opción 1: Ejecutar el archivo

Puedes ejecutar el juego directamente haciendo doble clic en el archivo `run` que se encuentra en la carpeta del proyecto.
Esto abrirá automáticamente una consola con el juego corriendo.

---

### 🛠️ Opción 2: Compilar manualmente

1. Abre la consola de Visual Studio Code.
2. Compila el programa con el siguiente comando:

```bash
gcc main.c src\extra.c src\hashmap.c src\list.c src\menu.c src\queue.c src\game.c -o bin\run.exe -lwinmm
```

3. Luego ejecútalo con:

```bash
bin\run.exe
```

---

### 🔧 Requisitos previos (sólo si deseas compilarlo manualmente)

- Tener instalado **Visual Studio Code.**
- Instalar la extensión para **C/C++**.
- Tener instalado un compilador para C, como **MinGW.**

---

### 📂 Archivos requeridos (Incluídos en el juego)

- `/bin`: almacena el código compilado.
- `/data`: datos que requiera el juego para funcionar (audios, imágenes, etc..)
- `/include` y `/src` : funciones ordenadas que necesita el juego.
- `main.c` : código base del juego.

---

### 🔨 Comentario como grupo

- Como grupo nos fue muy fácil trabajar, programamos siempre juntos, ya sea presencialmente o por discord, por lo que el trabajo fue equitativamente bien distribuido. No tuvimos ningún tipo de inconveniente al realizar el juego.

---

### 🐞 Posibles problemas encontrados

- **Soporte**: solo Windows, usuarios de MacOS podrían tener dificultades ejecutando el programa.
- **Entrada inválida**: si se ingresan caracteres cuando se solicita un número, el programa puede trabarse.
