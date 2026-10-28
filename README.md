# JARVIS local

Prototipo de escritorio para Linux con interfaz Tkinter, conversación, generador de contenido y creador de presentaciones con un modelo Ollama local, ficha persistida en este equipo y entrada/salida de voz opcionales. No usa una API remota ni controla el sistema operativo.

## Requisitos

- Python 3.10 o posterior y Tkinter.
- [Ollama](https://ollama.com/) instalado, iniciado y con un modelo descargado.
- Para voz: micrófono, `sounddevice`, `vosk` y el modelo de reconocimiento en español.
- Para respuestas habladas: `espeak-ng`.

En Debian/Ubuntu, los componentes del sistema se pueden instalar con:

```bash
sudo apt install python3-tk portaudio19-dev espeak-ng
```

## Preparación

Desde esta carpeta:

```bash
python3 -m venv .venv
source .venv/bin/activate
python -m pip install -r requirements.txt
ollama pull qwen2.5:3b
python jarvis_app.py
```

Si usas otro modelo, configura `JARVIS_MODEL` antes de iniciar la aplicación. El valor predeterminado es `qwen2.5:3b`.

Para activar el reconocimiento de voz, descarga el modelo pequeño en español de [Vosk](https://alphacephei.com/vosk/models):

```bash
mkdir -p models
unzip vosk-model-small-es-0.42.zip -d models
```

La carpeta final debe ser `models/vosk-model-small-es-0.42`. El botón de voz graba cinco segundos por solicitud. La conversación por texto funciona sin instalar las dependencias opcionales de voz, pero requiere Ollama para generar respuestas.

La ficha se guarda en `~/.config/jarvis/profile.json`. Las conversaciones no se guardan al cerrar la aplicación. Los mensajes se envían únicamente al servidor local de Ollama, que por defecto escucha en `http://localhost:11434`.

## Generador de presentaciones

En **Presentaciones**, introduce el tema o tus notas, el público, el número total de diapositivas (de 3 a 20, incluida la portada) y el estilo. JARVIS crea una presentación HTML independiente que se guarda en `~/.local/share/jarvis/presentaciones/` (o en `$XDG_DATA_HOME/jarvis/presentaciones/`). Se abre en el navegador para navegar con las flechas, presentar en pantalla completa y usar **Guardar como PDF** desde la impresión del navegador. El archivo HTML se puede compartir; no se publica automáticamente en internet. Las diapositivas usan diseño CSS y descripciones visuales, sin buscar ni descargar imágenes.

## Generador de contenido

Abre la pestaña **Crear contenido**, completa tu actividad, público, plataformas, objetivo del mes y tono, y pulsa **Crear mi contenido**. La app solicita al modelo un calendario de 30 días, tres guiones de reels y un carrusel de siete diapositivas. Puedes copiar el resultado completo o una sección. El contenido se conserva en pantalla mientras la aplicación esté abierta; no se guarda automáticamente.

## Alcance de esta versión

La skill original de `jarvis/` describe flujos para Claude, pero no es una aplicación ejecutable ni puede proporcionar por sí sola voz, memoria o acceso a herramientas. Este prototipo añade chat de escritorio local, ficha personal, generador de contenido y presentaciones; no lee correo, calendario ni otros archivos, no ejecuta comandos y no trabaja en segundo plano.
