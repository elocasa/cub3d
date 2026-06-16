# cub3d

Implementación base de **cub3D** con:
- parser de `.cub` (texturas, colores y mapa)
- validación de mapa (cerrado, caracteres válidos, jugador único)
- raycasting DDA con texturas por orientación
- movimiento y rotación con colisiones

## Estructura
- `/src`: código fuente
- `/include`: headers
- `/maps`: mapas de prueba válidos/ inválidos
- `/textures`: texturas XPM de ejemplo

## Compilar
```bash
make
```

> Requiere MiniLibX Linux en `./minilibx-linux`.

## Ejecutar
```bash
./cub3D maps/valid.cub
```

## Controles
- `W/S`: avanzar / retroceder
- `A/D`: strafe izquierda / derecha
- `←/→`: rotar
- `ESC` o cerrar ventana: salir

## Pruebas manuales mínimas
- Mapa válido: `./cub3D maps/valid.cub`
- Mapa abierto (debe fallar): `./cub3D maps/invalid_open.cub`
- Dos jugadores (debe fallar): `./cub3D maps/invalid_multi_player.cub`
- Carácter inválido (debe fallar): `./cub3D maps/invalid_char.cub`
