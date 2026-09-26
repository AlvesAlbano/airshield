const form = document.getElementById("wifiForm");
const nomeRede = document.getElementById("nomeRede");
const senhaRede = document.getElementById("senhaRede");
const mostrarSenha = document.getElementById("mostrarSenha");
const btnSalvar = document.getElementById("btnSalvar");
const mensagem = document.getElementById("mensagem");


// Mostrar / ocultar senha
mostrarSenha.addEventListener("click", function () {

    if (senhaRede.type === "password") {

        senhaRede.type = "text";
        mostrarSenha.textContent = "Ocultar";

    } else {

        senhaRede.type = "password";
        mostrarSenha.textContent = "Mostrar";

    }

});


// Enviar credenciais para o ESP32
form.addEventListener("submit", async function (event) {

    event.preventDefault();

    const ssid = nomeRede.value.trim();
    const senha = senhaRede.value;

    if (ssid === "") {
        mostrarMensagem("Digite o nome da rede.", "erro");
        return;
    }

    if (senha === "") {
        mostrarMensagem("Digite a senha da rede.", "erro");
        return;
    }

    btnSalvar.disabled = true;
    btnSalvar.textContent = "Salvando...";

    try {

        const resposta = await fetch("/salvar", {

            method: "POST",

            headers: {
                "Content-Type": "application/json"
            },

            body: JSON.stringify({
                ssid: ssid,
                senha: senha
            })

        });

        if (!resposta.ok) {
            throw new Error("Erro ao salvar");
        }

        mostrarMensagem(
            "Configuração salva com sucesso!",
            "sucesso"
        );

        btnSalvar.textContent = "Salvo";

    } catch (erro) {

        console.error(erro);

        mostrarMensagem(
            "Erro ao enviar os dados para o ESP32.",
            "erro"
        );

        btnSalvar.disabled = false;
        btnSalvar.textContent = "Salvar configuração";
    }

});


function mostrarMensagem(texto, tipo) {

    mensagem.textContent = texto;

    mensagem.className = tipo;

}
