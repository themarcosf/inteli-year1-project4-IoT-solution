# Inteli - Instituto de Tecnologia e Liderança

<p align="center">
<a href= "https://www.inteli.edu.br/"><img src="https://www.inteli.edu.br/wp-content/uploads/2021/08/20172028/marca_1-2.png" alt="Inteli - Instituto de Tecnologia e Liderança" border="0"></a>
</p>

# IoT para localização indoor de objetos - Atech

## Sauron

## Integrantes
- Alysson Cordeiro
- Bruno Moitinho Leão
- Felipe Saadi
- Iago Tavares
- Luiz Carlos da Silva Júnior
- Luiz Ferreira
- Marcos Florencio

## 📝 Descrição

A Atech é uma empresa brasileira, com sede em São Paulo, Brasil. O seu modelo de negócios é baseado em fornecer soluções tecnológicas e inovadoras para outras empresas. Fundada em 1997, a Atech é atualmente uma das maiores empresas atuando no setor de tráfego aéreo, entretanto, também tem atuação em outros setores como o de defesa.

Segundo a companhia, alguns dos seus clientes precisam rastrear seus ativos dentro de um local específico. Nosso projeto visa desenvolver um mvp capaz de fazer a localização dos ativos, a solução inclui tanto o sofware quanto o hardware.

## 📁 Estrutura de pastas
|--> documentos<br>
  &emsp;| .DS_Store<br>
  &emsp;| IoTDoc - v4.docx<br>
  &emsp;| IoTDoc - v4.pdf<br>
  &emsp;| Manual de Instruções - v2.docx<br>
  &emsp;| Manual de Instruções - v2.pdf<br>

|--> imagens<br>

|--> src<br>
  &emsp;|--> Backend <br>
    &emsp; &emsp;|--> controllers<br>
      &emsp; &emsp;&emsp;|categoryController.js<br>
      &emsp; &emsp;&emsp;|errController.js<br>
      &emsp; &emsp;&emsp;|tagsController.js<br>
      &emsp; &emsp;&emsp;|usersController.js<br>
  &emsp; &emsp;|--> models<br>
      &emsp; &emsp;&emsp;|categoryModel.js<br>
      &emsp; &emsp;&emsp;|tagModel.js<br>
      &emsp; &emsp;&emsp;|usersModel.js<br>
  &emsp; &emsp;|--> routers<br>
      &emsp; &emsp;&emsp;|categoryRouter.js<br>
      &emsp; &emsp;&emsp;|tagsRouter.js<br>
      &emsp; &emsp;&emsp;|usersRouter.js<br>
  &emsp; &emsp;|--> utils<br>
      &emsp; &emsp;&emsp;|convertion.js<br>
      &emsp; &emsp;&emsp;|lib.js<br>
      &emsp; &emsp;&emsp;|triangulation.js<br>

  &emsp;|--> Circuito <br>
    &emsp;&emsp;| beacon.ino<br>
    &emsp;&emsp;| beacon1<br>
    &emsp;&emsp;| beacon2.ino<br>
    &emsp;&emsp;| beacon3.ino<br>
    &emsp;&emsp;| tag.ino<br>
      
  &emsp;|--> Frontend<br>
    &emsp;&emsp;|-->public<br>
    &emsp;&emsp;&emsp;|vite.svg<br>
    &emsp;&emsp;|-->src<br>
      &emsp;&emsp;&emsp;|-->assets<br>
        &emsp;&emsp;&emsp;&emsp;|blueprint.png<br>
        &emsp;&emsp;&emsp;&emsp;|blueprint2.png<br>
        &emsp;&emsp;&emsp;&emsp;|blueprint3.png<br>
        &emsp;&emsp;&emsp;&emsp;|blueprint4.png<br>
        &emsp;&emsp;&emsp;&emsp;|blueprint5.png<br>
        &emsp;&emsp;&emsp;&emsp;|location.png<br>
        &emsp;&emsp;&emsp;&emsp;|logo.png<br>
        &emsp;&emsp;&emsp;&emsp;|logo2.png<br>
      &emsp;&emsp;&emsp;|-->main/routes<br>
        &emsp;&emsp;&emsp;&emsp;|router.tsx<br>
      &emsp;&emsp;&emsp;|-->presentation<br>
        &emsp;&emsp;&emsp;&emsp;&emsp;|-->components<br> 
          &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;|-->header<br>
          &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;|header.scss<br>
          &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;|header.tsx<br>
          &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;|-->sidebar<br>
          &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;|sidebar.scss<br>
          &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;|side.tsx<br>
          &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;|index.tsx<br>
        &emsp;&emsp;&emsp;&emsp;&emsp;|-->pages<br>
          &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;|-->acess<br>
          &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;|acess.scss<br>
          &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;|acess.tsx<br>
          &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;|-->aproval<br>
          &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;|aproval.scss<br>
          &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;|aproval.tsx<br>
          &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;|-->categories<br>
          &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;|categories.scss<br>
          &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;|categories.tsx<br>
          &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;|-->home<br>
          &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;|home.scss<br>
          &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;|home.tsx<br>
          &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;|-->location<br>
          &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;|location.scss<br>
          &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;|location.tsx<br>
          &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;|-->login<br>
          &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;|login.scss<br>
          &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;|login.tsx<br>
          &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;|-->settings<br>
          &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;|settings.scss<br>
          &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;|settings.tsx<br>
          &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;|-->signup<br>
          &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;|signup.scss<br>
          &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;|signup.tsx<br>
          &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;|-->tags<br>
          &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;|tags.scss<br>
          &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;|tags.tsx<br>
          &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;|index.tsx<br>
         &emsp;&emsp;&emsp;&emsp;&emsp;|-->styles<br>
         &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;|global.scss<br>
      &emsp;&emsp;&emsp;|index.d.ts<br>
      &emsp;&emsp;&emsp;|main.tsx<br>
    &emsp;&emsp;| .gitignore<br>
    &emsp;&emsp;| package-lock.json<br>
    &emsp;&emsp;| package.json<br>
    &emsp;&emsp;| tsconfig.json<br>
    &emsp;&emsp;| tsconfig.node.json<br>
    &emsp;&emsp;| vite.config.ts<br>

|README.md
  

Dentre os arquivos presentes na raiz do projeto, definem-se:

- <b>README.md</b>: arquivo que serve como guia e explicação geral sobre o projeto (o mesmo que você está lendo agora).

- <b>documentos</b>: aqui estão todos os documentos do projeto.

- <b>src</b>: nesta pasta encontra-se todo o código fonte do modelo preditivo.


## 💻 Execução dos projetos

Seguir o manual de instrução corretamente.

## 🗃 Histórico de lançamentos

* 1.0 - 21/10/2022
    * Arquitetura da solução v1.
* 2.0 - 04/11/2022
    * Arquitetura da solução v2.
    * Código fonte do sitema.
    * Protótipo de interface com o usuário.
* 3.0 - 18/11/2022
    * Arquitetura da solução v3.
    * Código fonte do sistema.
    * Bloco central v2 e externos.
* 4.0 - 02/12/2022
    * Bloco central v3 - sistema completo
    * Código fonte do sistema
* 5.0 - 16/12/2022
    * Sistema completo construído (versão final).
    * Código fonte do sistema (versão final).
    * Documentação refinada.



## 📋 Licença/License

<img style="height:22px!important;margin-left:3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/cc.svg?ref=chooser-v1"> <img style="height:22px!important;margin-left:3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/by.svg?ref=chooser-v1">
<p xmlns:cc="http://creativecommons.org/ns#" xmlns:dct="http://purl.org/dc/terms/"><a property="dct:title" rel="cc:attributionURL" href="https://github.com/InteliProjects">Inteli</a> by <span property="cc:attributionName">Inteli, Alysson Cordeiro, Bruno Moitinho Leão, Felipe Saadi, Iago Tavares, Luiz Carlos da Silva Júnior, Luiz Ferreira, Marcos Florencio is licensed under <a href="http://creativecommons.org/licenses/by/4.0/?ref=chooser-v1" target="_blank" rel="license noopener noreferrer" style="display:inline-block;">Attribution 4.0 International</a>.</p>

## 🎓 Referências

Nossas referências foram apenas as aulas e o material fornecido pelo do Inteli.


