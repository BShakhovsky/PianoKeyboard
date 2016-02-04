# include "stdafx.h"
# include "Keyboard\NoteNames.h"

TEST(Notes, OctaveNo)
{
	ASSERT_DEBUG_DEATH(NoteNames::GetOctaveNumber(-1), "NOTE MUST BE A POSITIVE NUMBER");
	ASSERT_EQ(0, NoteNames::GetOctaveNumber(0));
	ASSERT_EQ(0, NoteNames::GetOctaveNumber(6));
	ASSERT_EQ(1, NoteNames::GetOctaveNumber(12));
}

TEST(Notes, NoteNo)
{
	ASSERT_DEBUG_DEATH(NoteNames::GetNoteNumber(-1), "NOTE MUST BE A POSITIVE NUMBER");
	ASSERT_EQ(0, NoteNames::GetNoteNumber(0));
	ASSERT_EQ(1, NoteNames::GetNoteNumber(13));
	ASSERT_EQ(2, NoteNames::GetNoteNumber(26));
	ASSERT_EQ(3, NoteNames::GetNoteNumber(39));
	ASSERT_EQ(4, NoteNames::GetNoteNumber(52));
	ASSERT_EQ(5, NoteNames::GetNoteNumber(65));
	ASSERT_EQ(6, NoteNames::GetNoteNumber(78));
	ASSERT_EQ(7, NoteNames::GetNoteNumber(91));
	ASSERT_EQ(8, NoteNames::GetNoteNumber(104));
	ASSERT_EQ(9, NoteNames::GetNoteNumber(117));
	ASSERT_EQ(10, NoteNames::GetNoteNumber(130));
	ASSERT_EQ(11, NoteNames::GetNoteNumber(143));
}

/************************************************************************************
TEST(Notes, NoteName)
{
	ASSERT_DEBUG_DEATH(NoteNames::GetNoteName(-1), "NOTE MUST BE A POSITIVE NUMBER");
	ASSERT_EQ(NOTE_NAMES::C,	NoteNames::GetNoteName(0));
	ASSERT_EQ(NOTE_NAMES::C1,	NoteNames::GetNoteName(13));
	ASSERT_EQ(NOTE_NAMES::D,	NoteNames::GetNoteName(26));
	ASSERT_EQ(NOTE_NAMES::D1,	NoteNames::GetNoteName(39));
	ASSERT_EQ(NOTE_NAMES::E,	NoteNames::GetNoteName(52));
	ASSERT_EQ(NOTE_NAMES::F,	NoteNames::GetNoteName(65));
	ASSERT_EQ(NOTE_NAMES::F1,	NoteNames::GetNoteName(78));
	ASSERT_EQ(NOTE_NAMES::G,	NoteNames::GetNoteName(91));
	ASSERT_EQ(NOTE_NAMES::G1,	NoteNames::GetNoteName(104));
	ASSERT_EQ(NOTE_NAMES::A,	NoteNames::GetNoteName(117));
	ASSERT_EQ(NOTE_NAMES::A1,	NoteNames::GetNoteName(130));
	ASSERT_EQ(NOTE_NAMES::B,	NoteNames::GetNoteName(143));
}
************************************************************************************/