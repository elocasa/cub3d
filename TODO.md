## ✅ To-Do del proyecto cub3d

### 1) Base del proyecto
- [ ] Separar responsabilidades en `main`, `parser`, `render`, `input`, `game`, `free`
- [ ] Asegurar `Makefile` con flags `-Wall -Wextra -Werror` y dependencias `.d`
- [ ] Verificar que `minilibx-linux` compile y enlace correctamente
- [ ] Documentar requisitos del sistema y comandos de compilación/ejecución
- [ ] Añadir ejemplos de uso con mapas válidos e inválidos

### 2) Parsing del mapa/config
- [x] Abrir el fichero `.cub` y rechazar errores de acceso/lectura
- [x] Leer cabeceras `NO`, `SO`, `WE`, `EA` y guardar rutas de textura
- [x] Validar que no falte ninguna textura y que no haya duplicados
- [x] Parsear colores `F` y `C` en formato `R,G,B`
- [x] Comprobar que los valores RGB estén entre 0 y 255
- [x] Localizar el bloque del mapa tras las cabeceras y líneas vacías
- [x] Validar caracteres permitidos: `0`, `1`, espacios y posición inicial
- [x] Detectar exactamente una posición de jugador (`N`, `S`, `E`, `W`)
- [ ] Verificar que el mapa esté cerrado por paredes
- [ ] Rellenar el mapa a ancho uniforme para evitar accesos fuera de rango

### 3) Motor raycasting
- [x] Inicializar posición del jugador en el centro de la celda de inicio
- [x] Configurar dirección inicial y plano de cámara según orientación
- [x] Lanzar un rayo por cada columna de pantalla 000000
- [x] Implementar DDA para recorrer celdas del mapa
- [x] Calcular distancia perpendicular para evitar efecto ojo de pez
- [x] Determinar el lado impactado para elegir textura correcta
- [x] Calcular coordenada horizontal de la textura (`tex_x`)
- [x] Escalar la textura verticalmente según la altura de pared
- [x] Dibujar pared usando el buffer de imagen
- [x] Aplicar sombreado básico según distancia o lado del impacto

### 4) Movimiento y controles
- [x] Mapear teclas `W`, `A`, `S`, `D` para desplazamiento
- [x] Mapear flechas izquierda/derecha para rotación
- [x] Aplicar movimiento adelante y atrás respecto a la dirección del jugador
- [x] Aplicar strafe lateral usando el plano de cámara
- [x] Separar movimiento en eje X y eje Y para mejorar colisiones
- [x] Bloquear avance cuando la siguiente celda sea pared
- [x] Evitar atravesar esquinas cerradas o paredes diagonales
- [x] Cerrar la ventana con `ESC` y con el evento de la ventana

### 5) Render y UX
- [x] Pintar techo con color uniforme antes de dibujar paredes
- [x] Pintar suelo con color uniforme en la mitad inferior
- [x] Mantener refresco continuo con `mlx_loop_hook`
- [x] Inicializar y liberar correctamente la imagen de frame
- [x] Cerrar ventana sin fugas de memoria ni recursos gráficos
- [ ] Definir si el minimapa entra en el alcance o queda fuera
- [ ] Añadir ayudas visuales opcionales para depuración si hace falta

### 6) Robustez
- [ ] Centralizar salida de error con mensaje consistente
- [ ] Liberar texturas, mapa, ventana, imagen y contexto MLX
- [ ] Comprobar rutas de textura con `access()` antes de cargar
- [ ] Validar entradas vacías o malformadas con mensajes claros
- [ ] Evitar dobles liberaciones en cierres normales o por error
- [ ] Probar mapas válidos con distintas orientaciones del jugador
- [ ] Probar mapas inválidos: abiertos, múltiples jugadores, caracteres raros
- [ ] Probar que el juego no crashea al cerrar durante carga o ejecución

### 7) Entrega
- [ ] Revisar estilo de nombres, indentación y funciones pequeñas
- [ ] Confirmar compilación limpia sin warnings ni errores
- [ ] Probar ejecución final con varios mapas de ejemplo
- [ ] Actualizar README con instalación, ejecución y controles
- [ ] Añadir notas sobre limitaciones conocidas y alcance final
