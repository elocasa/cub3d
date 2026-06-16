## ✅ To-Do del proyecto cub3d

### 1) Base del proyecto
- [ ] Separar responsabilidades en `main`, `parser`, `render`, `input`, `game`, `free`
- [ ] Asegurar `Makefile` con flags `-Wall -Wextra -Werror` y dependencias `.d`
- [ ] Verificar que `minilibx-linux` compile y enlace correctamente
- [ ] Documentar requisitos del sistema y comandos de compilación/ejecución
- [ ] Añadir ejemplos de uso con mapas válidos e inválidos

### 2) Parsing del mapa/config
- [ ] Abrir el fichero `.cub` y rechazar errores de acceso/lectura
- [ ] Leer cabeceras `NO`, `SO`, `WE`, `EA` y guardar rutas de textura
- [ ] Validar que no falte ninguna textura y que no haya duplicados
- [ ] Parsear colores `F` y `C` en formato `R,G,B`
- [ ] Comprobar que los valores RGB estén entre 0 y 255
- [ ] Localizar el bloque del mapa tras las cabeceras y líneas vacías
- [ ] Validar caracteres permitidos: `0`, `1`, espacios y posición inicial
- [ ] Detectar exactamente una posición de jugador (`N`, `S`, `E`, `W`)
- [ ] Verificar que el mapa esté cerrado por paredes
- [ ] Rellenar el mapa a ancho uniforme para evitar accesos fuera de rango

### 3) Motor raycasting
- [ ] Inicializar posición del jugador en el centro de la celda de inicio
- [ ] Configurar dirección inicial y plano de cámara según orientación
- [ ] Lanzar un rayo por cada columna de pantalla
- [ ] Implementar DDA para recorrer celdas del mapa
- [ ] Calcular distancia perpendicular para evitar efecto ojo de pez
- [ ] Determinar el lado impactado para elegir textura correcta
- [ ] Calcular coordenada horizontal de la textura (`tex_x`)
- [ ] Escalar la textura verticalmente según la altura de pared
- [ ] Dibujar pared usando el buffer de imagen
- [ ] Aplicar sombreado básico según distancia o lado del impacto

### 4) Movimiento y controles
- [ ] Mapear teclas `W`, `A`, `S`, `D` para desplazamiento
- [ ] Mapear flechas izquierda/derecha para rotación
- [ ] Aplicar movimiento adelante y atrás respecto a la dirección del jugador
- [ ] Aplicar strafe lateral usando el plano de cámara
- [ ] Separar movimiento en eje X y eje Y para mejorar colisiones
- [ ] Bloquear avance cuando la siguiente celda sea pared
- [ ] Evitar atravesar esquinas cerradas o paredes diagonales
- [ ] Cerrar la ventana con `ESC` y con el evento de la ventana

### 5) Render y UX
- [ ] Pintar techo con color uniforme antes de dibujar paredes
- [ ] Pintar suelo con color uniforme en la mitad inferior
- [ ] Mantener refresco continuo con `mlx_loop_hook`
- [ ] Inicializar y liberar correctamente la imagen de frame
- [ ] Cerrar ventana sin fugas de memoria ni recursos gráficos
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