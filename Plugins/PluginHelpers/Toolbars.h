#pragma once

////////////////////////////////////////////////////////////////////////////////////////////////

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Windows::Forms;
using namespace System::Drawing;

////////////////////////////////////////////////////////////////////////////////////////////////

struct UITHEME;

////////////////////////////////////////////////////////////////////////////////////////////////

namespace Abstractspoon
{
	namespace Tdl
	{
		namespace PluginHelpers
		{
			public ref class Toolbars
			{
			public:
				static void FixupButtonSizes(ToolStrip^ toolbar);
			};

			public ref class BaseToolbarRenderer : ToolStripProfessionalRenderer
			{
			public:
				BaseToolbarRenderer();

				void EnableDrawRowDividers(bool enable);

			private:
				bool m_DrawRowDividers;

			protected:
				virtual void OnRenderToolStripBackground(ToolStripRenderEventArgs^ e) override;

				virtual void DrawRowBackground(Drawing::Graphics^ g, Drawing::Rectangle^ rowRect, bool firstRow, bool lastRow);
				virtual void DrawRowDivider(Drawing::Graphics^ g, Drawing::Rectangle^ rowRect, bool firstRow, bool lastRow);
			};
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////

