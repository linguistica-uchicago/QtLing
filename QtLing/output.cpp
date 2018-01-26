#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QString>
#include "Lexicon.h"
#include "mainwindow.h"
#include "WordCollection.h"
#include "Word.h"

void MainWindow::write_stems_and_words()
{
    CLexicon* lexicon = get_lexicon();
    QString file_name;
    file_name = "../../../../Dropbox/data/english/lxa/parses.txt";
    CStem *     pStem;

    QFile out_file (file_name);

    if (! out_file.open(QFile::WriteOnly | QFile::Text))
    {
        qDebug() << "************  no file opened 17";
        return;
    }

    QTextStream out (&out_file);

    QMapIterator<QString,CWord*> word_iter (*lexicon->get_words()->get_map());
    while (word_iter.hasNext()){
        CWord* pWord = word_iter.next().value();
        if (pWord->get_parse_triples()->size() > 0){
            for  (int i = 0; i < pWord->get_parse_triples()->size(); i++ )
            {
                Parse_triple *  this_triple = pWord->get_parse_triples()->at(i);
                out << pWord->get_key() << "+" <<  this_triple->p_stem  << "+"<< this_triple->p_suffix << endl ;
            }
        }
        else
        {
            out  <<  pWord->get_key() <<  endl;
        }
    }
}

void MainWindow::read_stems_and_words()
{
    CLexicon* lexicon = get_lexicon();
    QString file_name = "../../../../Dropbox/data/english/lxa/parses.txt";

    QFile in_file (file_name);
    QTextStream in(&in_file);

    if (! in_file.open(QFile::ReadOnly | QIODevice::Text))
    {
        qDebug() << "************  no file opened ";
        return;
    }
    while (! in_file.atEnd()){
        QString line = in_file.readLine();
        line = line.trimmed();
        //qDebug() << line;
        QStringList words = line.split("+");
        if (words.size() == 3){
            //qDebug() << words[0] << words[1] << words[2];

            lexicon->get_parses()->append(QPair<QString,QString>(words[1], words[2]));
        }
        //qDebug() << line;
        lexicon->get_words()->add(words[0]);
    }
    lexicon->CreateStemAffixPairs();
    lexicon->AssignSuffixesToStems();
    load_models();
    create_or_update_TreeModel();

    set_up_graphics_scene_and_view();
    m_leftTreeView->expandAll();
    m_leftTreeView->resizeColumnToContents(0);

}
