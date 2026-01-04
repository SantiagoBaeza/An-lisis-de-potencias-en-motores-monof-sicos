[⬅️ Volver a "Proyectos en C y C++"](https://github.com/SantiagoBaeza/C-y-C-/tree/main)

# Análisis de potencias en motores monofásicos

Este proyecto implementa un programa en C que calcula la **potencia activa (P)** y la **potencia aparente (S)** de tres motores monofásicos, a partir de datos eléctricos almacenados en archivos binarios `.dat`.  
Cada archivo contiene muestras de tensión, corriente y tiempo en formato `double`, organizadas en secuencias de tres valores: `V C T`.  
El objetivo es determinar qué motor presenta el mayor valor de P y, al mismo tiempo, el menor valor de S.

---

## Contexto

Se trabajó con tres archivos (`motor1.dat`, `motor2.dat`, `motor3.dat`) que contenían registros de tensión, corriente y tiempo.  
El objetivo fue implementar un algoritmo que leyera los datos, calculara la **potencia activa (P)** y la **potencia aparente (S)** según las fórmulas dadas, y luego comparara los resultados entre los tres motores para identificar cuál cumplía la condición de mayor P y menor S. (tristemente los archivos .dat los perdí, sin embargo vale la pena analizar el fucionamiento del algoritmo)

Las fórmulas utilizadas fueron:

- **Potencia activa (P):**
- ![Potencia activa (P):](https://github.com/SantiagoBaeza/An-lisis-de-potencias-en-motores-monof-sicos/blob/main/01%20formula%20potencia%20activa%20.jpg)

- **Potencia aparente (S):**  
  La potencia Aparente (S) resulta de multiplicar la tenison RMS por la corriente RMS.

- **Valor RMS de una magnitud X:**  
  ![Valor RMS de una magnitud X](https://github.com/SantiagoBaeza/An-lisis-de-potencias-en-motores-monof-sicos/blob/main/02%20formula%20Valor%20RMS%20de%20la%20magnitud%20X.jpg)

---

## Explicación del algoritmo

1. **Lectura de archivos binarios:**  
   - Se abre cada archivo (`motor1.dat`, `motor2.dat`, `motor3.dat`) en modo binario.  
   - Se calcula la cantidad de registros dividiendo el tamaño del archivo por `sizeof(double)`, y luego agrupando de a tres valores (V, C, T).  
   - Se reserva memoria dinámica para almacenar los datos en un vector de estructuras.

2. **Carga de datos en estructuras:**  
   - Cada registro se guarda en un `struct datos` con tres campos: tensión, corriente y tiempo.  
   - Se repite este proceso para los tres motores.

3. **Cálculo de potencia activa (P):**  
   - Se recorre el vector sumando el producto `V * C` de cada muestra.  
   - El resultado se divide por la diferencia de tiempo entre el último y el primer registro.

4. **Cálculo de potencia aparente (S):**  
   - Se calcula el valor RMS de la tensión y de la corriente.  
   - Se multiplica `V_RMS * C_RMS` para obtener la potencia aparente.

5. **Comparación de resultados:**  
   - Se imprimen los valores de P y S para cada motor.  
   - Se determina cuál motor cumple la condición de mayor P y menor S, utilizando una comparación intermedia de los valores.

6. **Liberación de memoria:**  
   - Se libera la memoria dinámica reservada para cada vector de datos antes de finalizar el programa.

---

## Funcionalidad

- Lectura de archivos binarios con `fread`.  
- Uso de estructuras (`struct datos`) para organizar la información.  
- Cálculo de potencias activa y aparente mediante sumatorias y operaciones RMS.  
- Comparación de resultados entre tres motores.  
- Manejo de memoria dinámica con `malloc` y `free`.

---

## Tecnologías utilizadas

- Lenguaje C (estándar)  
- Librerías: `stdio.h`, `stdlib.h`, `math.h`  
- Archivos binarios `.dat` con datos eléctricos de motores monofásicos  
- Operaciones matemáticas para cálculo de potencia y RMS

---

## Comentarios finales

Este proyecto está diseñado para ejecutarse en consola y analizar el rendimiento de tres motores monofásicos.  
Aunque no se incluyen capturas de ejecución, el README compensa con una explicación detallada del algoritmo y del flujo del programa.  
Los archivos `.dat` originales contenían los datos necesarios para realizar las pruebas, y en su momento permitieron validar el correcto funcionamiento del programa.

Este ejercicio fue clave para reforzar conceptos de manejo de archivos binarios, estructuras, memoria dinámica y cálculos eléctricos en C.

---

> 🧩 Estos espacios están en construcción y se actualizan de forma frecuente.
