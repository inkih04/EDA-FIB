import subprocess
import random
import re

def ejecutar_juego(jugador):
    semilla = random.randint(40, 200)
    
    comando = f"./Game Dummy Dummy Dummy {jugador} -s {semilla} -i default.cnf -o default.res"
    resultado = subprocess.run(comando, shell=True, capture_output=True, text=True)
    return resultado.stderr

def obtener_puntuaciones(salida):
    patron_jugador = r"^(?!.*Dummy).*got score (\d+)"
    patron_victoria = r"XSMTETIN got top score"
    patron_max_score = r"player .* got score (\d+)"

    puntuacion_jugador = re.findall(patron_jugador, salida, re.MULTILINE)
    victoria = re.search(patron_victoria, salida, re.MULTILINE) is not None
    max_puntuaciones = re.findall(patron_max_score, salida, re.MULTILINE)

    max_puntuacion = max(map(int, max_puntuaciones), default=0) if max_puntuaciones else 0

    return int(puntuacion_jugador[-1]) if puntuacion_jugador else 0, victoria, max_puntuacion


puntuaciones = []
victorias = 0
diferencias = []
iteraciones = int(input("Numero de iteraciones: \n"))
jugador = input("Nombre jugador: \n")
for _ in range(iteraciones):
    salida = ejecutar_juego(jugador)
    puntuacion_jugador, victoria, max_puntuacion = obtener_puntuaciones(salida)
    puntuaciones.append(puntuacion_jugador)
    if victoria:
        victorias += 1
    else:
        diferencias.append(max_puntuacion - puntuacion_jugador)

media_puntuacion = sum(puntuaciones) / len(puntuaciones) if puntuaciones else 0
media_diferencia = sum(diferencias) / len(diferencias) if diferencias else 0

print("Media de puntuación:", media_puntuacion)
print("Total de victorias:", victorias)
print("Media de diferencia de puntuación en derrotas:", media_diferencia)

