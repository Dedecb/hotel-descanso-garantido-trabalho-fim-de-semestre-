🏨 Hotel Descanso Garantido — Sistema de Gestão
Trabalho Interdisciplinar – AEDs I & FES – PUC Minas (2025/2)

Desenvolvido por:

  André Luiz F. Rosa

  Gustavo Paulino Cícero

📌 Sobre o Projeto

Este projeto implementa um sistema de gerenciamento para o Hotel Descanso Garantido, atendendo às exigências das disciplinas Algoritmos e Estruturas de Dados I e Fundamentos de Engenharia de Software.

O objetivo é substituir os controles manuais por um sistema em C++, com armazenamento persistente usando arquivos binários, garantindo organização das informações do hotel.

🧩 Funcionalidades do Sistema

Todas as funcionalidades foram extraídas diretamente do enunciado do trabalho.

✔️ Cadastro

  Cadastro de clientes

  Cadastro de funcionários

  Cadastro de quartos

  Cadastro de estadias

✔️ Validações obrigatórias

  Código de cliente não pode repetir

  Código de funcionário não pode repetir

  Número de quarto não pode repetir

  Só é possível cadastrar estadia se:

  Cliente existir

  Quarto existir

  Quarto estiver desocupado

  Não houver estadia no mesmo período para o mesmo quarto

  A capacidade do quarto suportar a quantidade de hóspedes

✔️ Operações com estadias

  Calcular número de diárias automaticamente com base nas datas

  Registrar o quarto como ocupado ao criar a estadia

  Dar baixa na estadia

  Calcular e exibir o valor total da estadia

  Alterar quarto para desocupado ao finalizar

✔️ Pesquisas

  Buscar cliente por nome ou código

  Buscar funcionário por nome ou código

  Mostrar todas as estadias de um cliente (por nome ou código)

✔️ Outras funcionalidades

  Cálculo de pontos de fidelidade do cliente

  10 pontos por diária

  Menu principal com loop até o usuário escolher sair

  Salvamento e carregamento de dados usando arquivos binários (.dat)

  Organização do código em módulos e bibliotecas (.c e .h)
