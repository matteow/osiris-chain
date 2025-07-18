// Poprawny sposób importowania w modułach ES
import 'dotenv/config';
import { GoogleGenerativeAI } from "@google/generative-ai";

// Inicjalizuje klienta, używając klucza API z pliku .env
const genAI = new GoogleGenerativeAI(process.env.GEMINI_API_KEY);

async function main() {
  try {
    // Wybiera poprawny model
    const model = genAI.getGenerativeModel({ model: "gemini-1.5-flash" });

    // Generuje treść
    const result = await model.generateContent("Explain how AI works in a few words");

    // Poprawnie odczytuje odpowiedź
    const text = result.response.text();
    console.log(text);

  } catch (error) {
    console.error("Wystąpił błąd:", error.message);
  }
}

main();
